// ProgrammedMenu.cpp by Ulrich Eisenecker, July 9, 2025

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <stdexcept>

class InvisibleNode: public Fl_Group
{
   public:
      InvisibleNode(int x, int y, int w, int h,
                    const char* label = nullptr
                   ):Fl_Group { x,y,w,h,label }
      {}
      virtual void draw() override
      {
         draw_children();
      }
      void end();
};

class Node;

Node* asNode(Fl_Widget* widget);

class Node: public InvisibleNode
{
   public:
      Node(int x, int y, int w, int h, const char* label = nullptr,
           Fl_Color c = FL_BLACK):InvisibleNode { x,y,w,h,label },
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
            this->changeResizableUpwards(this);
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
               m_focused =
               asNode(parent()->child(index));
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
         auto parentNode { asNode(parent()) };
         if (parentNode && parentNode->take_focus())
         {
            m_focused = parentNode;
            redraw();
         }
      }
      void focusChild()
      {
         auto node { asNode(this) };
         if (node && node->children() > 0)
         {
            if (node->child(0)->take_focus())
            {
               m_focused = node->child(0);
               redraw();
            }
         }
      }
      bool inside(int x,int y,int w,int h)
      {
         if (x >= 0 && x < w &&
             y >= 0 && y < h)
         {
            return true;
         };
         return false;
      }
      bool focusWidget(int ev_x = Fl::event_x(),int ev_y = Fl::event_y())
      {
         auto node { asNode(this) };
         if (node == nullptr)
         {
            return false;
         }
         for (int i { 0 };i < node->children();++i)
         {
            auto childNode { asNode(node->child(i)) };
            if (childNode && childNode->focusWidget(ev_x,ev_y))
            {
               return true;
            }
         }
         if (inside(ev_x - x(),ev_y - y(),w(),h()))
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
                 break;
            case FL_FOCUS:
                 redraw();
                 return 1;
                 break;
            case FL_KEYBOARD:
                 {
                    auto key { Fl::event_key() };
                    switch (key)
                    {
                       case FL_Tab :
                            if (Fl::event_state() == FL_SHIFT)
                            {
                               focusPreviousSibling();
                               return 1;
                            }
                            else
                            {
                              focusNextSibling();
                              return 1;
                            }
                            break;
                       case FL_Right :
                            focusNextSibling();
                           return 1;
                            break;
                       case FL_Left :
                            focusPreviousSibling();
                            return 1;
                            break;
                       case FL_Up :
                            focusParent();
                            return 1;
                            break;
                       case FL_Down :
                            focusChild();
                            return 1;
                            break;
                    };
                 };
                 break;
            case FL_UNFOCUS:
                 redraw();
                 return 1;
                 break;
         }
         Fl::focus(m_focused);
         return Fl_Widget::handle(event);
      }
      static Fl_Widget* focused()
      {
         return m_focused;
      }
   private:
      Fl_Color m_color;
      inline static Fl_Widget* m_focused { nullptr };
};

void InvisibleNode::end()
{
   Fl_Group::end();
   if (children())
   {
      auto node { asNode(child(0)) };
      if (node)
      {
         node->focus();
      }
   }
}

Node* asNode(Fl_Widget* widget)
{
   return dynamic_cast<Node*>(widget);
}

void cb(Fl_Widget*,void* data)
{
   static_assert(sizeof(unsigned long) == sizeof(void*));
   auto value { reinterpret_cast<unsigned long&>(data) };
   switch (value)
   {
      case 1: fl_message("Menu application, July 9, 2025\n"
                         "by Ulrich Eisenecker");
              break;
      case 2: if (fl_choice("Do you really want to quit the program?",
                  "Ok","Cancel",0) == 0)
              {
                 exit(0);
              }
              break;
      case 3: asNode(Node::focused())->changeColor();
              break;
      case 4: asNode(Node::focused())->changeLabel();
              break;
      case 5: asNode(Node::focused())->changeResizable();
              break;
      default:fl_alert("Unknown menu item %ld",value);
              break;
   }
}

int main()
{
   // window /////////////////////////
   Fl_Window window { 640,480,"Parent" };
   // menuBar in window //////////////
   Fl_Menu_Bar menuBar { 0,0,window.w(),30,"Menu" };
   menuBar.add("Demo/_&About",FL_CTRL+'a',cb,(void*)1ul);
   menuBar.add("Demo/Quit",   FL_ALT +'q', cb,(void*)2ul);

   menuBar.add("Edit/&Color",    "#c", cb,reinterpret_cast<void*>(3ul));
   menuBar.add("Edit/&Label",    "+l", cb,reinterpret_cast<void*>(4ul));
   menuBar.add("Edit/_&Resizable","^c",cb,reinterpret_cast<void*>(5ul));
   menuBar.add("Edit/_&Unknown",  0,   cb,reinterpret_cast<void*>(6ul));

   // Some computations ///////////////
   auto wHalf { window.w() / 2 };
   auto hHalf { (window.h() - menuBar.h()) / 2 };

   // invisible in window /////////////
   InvisibleNode invisible { 0,menuBar.h(),window.w(),window.h() - menuBar.h() };
   // green in invisible //////////////
   Node green { 0,menuBar.h(),wHalf,hHalf,"Green",FL_GREEN };
   // red in green ////////////////////
   Node red { green.w() / 6,green.h() / 6 + menuBar.h(),
              green.w() / 3,green.h() / 2,"Red",FL_RED };
   red.align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
   // blue in red /////////////////////
   Node blue { red.x() + 5,red.y() + 5,35,20,"Blue",FL_BLUE };
   blue.align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
   // blue end ////////////////////////
   blue.end();
   // red end /////////////////////////
   red.end();
   // white in green //////////////////
   Node white { green.w() * 2 / 3,green.h() * 2 / 3,
                green.w() / 4,green.h() / 4,"White",FL_WHITE };
   white.align(FL_ALIGN_CENTER | FL_ALIGN_INSIDE);
   // white in green //////////////////
   white.end();
   // green end ///////////////////////
   green.end();
   // magenta in invisble /////////////
   Node magenta { wHalf,menuBar.h(),wHalf,hHalf,"Magenta",FL_MAGENTA };
   // magenta end /////////////////////
   magenta.end();
   // cyan in invisible ///////////////
   Node cyan { 0,hHalf + menuBar.h(),wHalf,hHalf,"Cyan",FL_CYAN };
   // cyan end ////////////////////////
   cyan.end();
   // yellow in invisible /////////////
   Node yellow { wHalf,hHalf + menuBar.h(),wHalf,hHalf,"Yellow",FL_YELLOW };
   // yellow end //////////////////////
   yellow.end();
   // invisible end ///////////////////
   invisible.end();
   for (int n { 0 }; n < invisible.children(); ++n)
   {
      invisible.child(n)->align(FL_ALIGN_TOP | FL_ALIGN_INSIDE);
   }
   // window end //////////////////////
   window.end();
   window.resizable(invisible);
   window.show();
   return Fl::run();
}
