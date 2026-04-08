// NestedChildren.cpp by Ulrich Eisenecker, March 14, 2024

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Color_Chooser.H>

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
         Node* parentNode { dynamic_cast<Node*>(parent()) };
         if (parentNode)
         {
            parentNode->changeResizableUpwards(this);
         }
      }
      void resetResizableDownwards()
      {
         for (int i { 0 };i < children(); ++i)
         {
            Node* node { dynamic_cast<Node*>(child(i)) };
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
         // The following statement uses the ternary operator.
         Fl_Boxtype boxtype { m_focused == this ? FL_DOWN_BOX : FL_UP_BOX };
         draw_box(boxtype,m_color);
         draw_label();
         draw_children();
      }
      int handle(int event) override
      {
         switch (event)
         {
            case FL_PUSH:
            // The statements of this case branch contain serious errors.
                 if (children())
                 {
                    for (int i { 0 };i < children();++i)
                    {
                       if (Fl::event_inside(child(i)))
                       {
                          if (child(i)->take_focus())
                          {
                             m_focused = child(i);
                             return 1;
                          };
                       }
                    }
                 }
                 if (take_focus())
                 {
                    m_focused = this;
                    return 1;
                 }
                 break;
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
   return Fl::run();
}
