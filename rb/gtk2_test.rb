#!/usr/bin/ruby

require 'gtk'
#require 'gtk2'
#Gtk.init

start_button = Gtk::Button.new("start")
start_button.signal_connect("clicked") do
  unless @th
    @th = Thread.new {
      (0...10).each { |cnt|
        sleep(1)
        puts "cnt = #{cnt}\n"
        cnt += 1
      }
      puts "finished"
      @th = nil
    }
  end
end
stop_button = Gtk::Button.new("stop")
stop_button.signal_connect("clicked") do
  if @th
    @th.kill
    puts "killed"
    @th = nil
  end
end

box = Gtk::VBox.new.add(start_button).add(stop_button)
Gtk::Window.new.add(box).show_all

Gtk.main
