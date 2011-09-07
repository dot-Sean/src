#!/usr/bin/env ruby

require 'gtk'

class GtkTest
  Str = "Hello, world."
  def initialize
    window = Gtk::Window.new(Gtk::WINDOW_TOPLEVEL)
      window.add(box = Gtk::VBox.new(FALSE, 0))
        box.pack_start(text = Gtk::Text.new())
        text.show
        # ------------------------------------------------------------
        box.pack_start(button = Gtk::Button.new("append"))
        button.signal_connect("clicked") {
          text.insert_text(Str + "\n", text.get_point)
        }
        button.show
      box.show
    window.set_title("gtk_test")
    window.signal_connect("delete_event") {
      exit
    }
    window.signal_connect("destroy_event") {
      exit
    }
    window.show
  end
  def run
    Gtk::main()
  end
end

gtktest = GtkTest::new
gtktest.run
