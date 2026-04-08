// NestedChildrenImproved.cpp by Ulrich Eisenecker, July 09, 2025

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Color_Chooser.H>
#include <stdexcept>

bool within(int x,int y,int w,int h)
{
   if (x >= 0 && x < w &&
       y >= 0 && y < h)
   {
      return true;
   };
   return false;
}

class Node; // Pending declaration

// Declaration of function casting to Node*
Node* asNode(Fl_Widget* widget);

class Node: public Fl_Group
{
   public:
      Node(int x, int y, int w, int h, const char* label = nullptr,
           Fl_Color c = FL_BLACK):Fl_Group { x,y,w,h,label },
           m_color { c }
      {}
      void changeColor()
      {
         uchar r,g,b;
         Fl::get_color(m_color,r,g,b);
         if (fl_color_chooser("Select color",r,g,b) == 1)
         {
            m_color = fl_rgb_color(r,g,b);
            redraw();
         }
      }
      void changeLabel()
      {
         auto newLabel { fl_input("New label: ",label()) };
         if (newLabel)
         {
            copy_label(newLabel);
            redraw();
         }
      }
      void changeResizableUpwards(Fl_Widget* node)
      {
         parent()->resizable(node);
         parent()->init_sizes();
         auto parentNode { asNode(parent()) };
         if (parentNode)
         {
            parentNode->changeResizableUpwards(this);
         }
      }
      void resetResizableDownwards()
      {
         for (int i { 0 };i < children(); ++i )
         {
            auto node { asNode(child(i)) };
            if (node)
            {
               node->resizable(nullptr);
               node->resetResizableDownwards();
            }
         }
         resizable(this);
         init_sizes();
      }
      void changeResizable()
      {
         if (fl_choice("Make %s the resizable widget?",
                       "Yes","No",0,label()) == 0)
         {
            resetResizableDownwards();
            changeResizableUpwards(this);
         }
      }
      void draw() override
      {
         Fl_Boxtype boxtype { m_focused == this ? FL_DOWN_BOX : FL_UP_BOX };
         draw_box(boxtype,m_color);
         draw_label();
         draw_children();
      }
      void focusNextSibling()
      {
         if (parent())
         {
            if (parent()->children() == 0)
            {
               throw std::out_of_range
                     { "focusNextSibling() - no. of children is zero" };
            }
            auto index { parent()->find(this) };
            if (index == parent()->children())
            {
               throw std::out_of_range
                     { "focusNextSibling() - child not in group" };
            }
            if (index == parent()->children() - 1)
            {
               index = 0;
            }
            else
            {
               ++index;
            }
            if (parent()->child(index)->take_focus())
            {
               m_focused = parent()->child(index);
               redraw();
            }
         }
      }
      void focusPreviousSibling()
      {
         if (parent())
         {
            if (parent()->children() == 0)
            {
               throw std::out_of_range
                     { "focusPreviousSibling() - no. of children is zero" };
            }
            auto index { parent()->find(this) };
            if (index == parent()->children())
            {
               throw std::out_of_range
                     { "focusPreviousSibling() - child not in group" };
            }
            if (index == 0)
            {
               index = parent()->children() - 1;
            }
            else
            {
               --index;
            }
            if (parent()->child(index)->take_focus())
            {
               m_focused = parent()->child(index);
               redraw();
            }
         }
      }
      void focusParent()
      {
         // Only Node's should take focus!
         auto parentNode { asNode(parent()) };
         if (parentNode && parentNode->take_focus())
         {
            m_focused = parentNode;
            redraw();
         }
      }
      void focusChild()
      {
         if (children() > 0 && child(0)->take_focus())
         {
            m_focused = child(0);
            redraw();
         }
      }
      bool focusWidget(int ev_x = Fl::event_x(),int ev_y = Fl::event_y())
      {
         for (int i { 0 };i < children();++i)
         {
            auto childNode { asNode(child(i)) };
            if (childNode && childNode->focusWidget(ev_x,ev_y))
            {
               return true;
            }
         }
         if (within(ev_x - x(),ev_y - y(),w(),h()))
         {
            m_focused = this;
            redraw();
            return true;
         }
         return false;
      }
      Fl_Widget* focus()
      {
         if (take_focus())
         {
            m_focused = this;
            return m_focused;
         }
         return nullptr;
      }
      int handle(int event) override
      {
         switch (event)
         {
            case FL_PUSH:
                 focusWidget();
                 return 1;
            case FL_FOCUS:
                 redraw();
                 return 1;
            case FL_KEYBOARD:
                 {
                    auto key { Fl::event_key() };
                    switch (key)
                    {
                       case 'c':
                            changeColor();
                            return 1;
                       case 'l':
                            changeLabel();
                            return 1;
                       case 'r':
                            changeResizable();
                            return 1;
                       case FL_Tab:
                            if (Fl::event_state() == FL_SHIFT)
                            {
                               focusPreviousSibling();
                            }
                            else
                            {
                              focusNextSibling();
                            }
                            return 1;
                       case FL_Right:
                            focusNextSibling();
                            return 1;
                       case FL_Left:
                            focusPreviousSibling();
                            return 1;
                       case FL_Up:
                            focusParent();
                            return 1;
                       case FL_Down:
                            focusChild();
                            return 1;
                    };
                 };
                 break;
            case FL_UNFOCUS:
                 redraw();
                 return 1;
         }
         Fl::focus(m_focused);
         return Fl_Widget::handle(event);
      }
   private:
      Fl_Color m_color;
      inline static Fl_Widget* m_focused { nullptr };
};

Node* asNode(Fl_Widget* widget)
{
   return dynamic_cast<Node*>(widget);
}

int main()
{
   // window /////////////////////////
   Fl_Window window { 320,240,"Parent" };

   // Some computations ///////////////
   auto wHalf { window.w() / 2 };
   auto hHalf { window.h() / 2 };

   // green in window /////////////////
   Node green { 0,0,wHalf,hHalf,"Green",FL_GREEN };
   // red in green ////////////////////
   Node red { green.w() / 6,green.h() / 6,
              green.w() / 3,green.h() / 3,"Red",FL_RED };
   red.align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
   // red end /////////////////////////
   red.end();
   // white in green //////////////////
   Node white { green.w() * 2 / 3,green.h() * 2 / 3,
                green.w() / 4,green.h() / 4,"White",FL_WHITE };
   white.align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
   // white end ///////////////////////
   white.end();
   // green end ///////////////////////
   green.end();
   // magenta in window ///////////////
   Node magenta { wHalf,0,wHalf,hHalf,"Magenta",FL_MAGENTA };
   // magenta end /////////////////////
   magenta.end();
   // cyan in window //////////////////
   Node cyan { 0,hHalf,wHalf,hHalf,"Cyan",FL_CYAN };
   // cyan end ////////////////////////
   cyan.end();
   // yellow in window ////////////////
   Node yellow { wHalf,hHalf,wHalf,hHalf,"Yellow",FL_YELLOW };
   // yellow end /////////////////////
   yellow.end();
   for (int n { 0 }; n < window.children(); ++n)
   {
     window.child(n)->align(FL_ALIGN_TOP | FL_ALIGN_INSIDE);
   }
   // window end //////////////////////
   window.end();
   window.resizable(window);
   window.show();
   if (window.children())
   {
      for (int i { 0 };i < window.children();++i)
      {
         auto node { asNode(window.child(i)) };
         if (node && node->focus())
         {
            break;
         }
      }
   }
   return Fl::run();
}
