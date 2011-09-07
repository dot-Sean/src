#!/usr/bin/ruby
# -*- coding: utf-8 -*-

module BaseMixin
  def initialize
    print "BaseMixin initialized\n"
  end
end

module DerivedMixin1
  include BaseMixin
  def initialize
    super
    print "DerivedMixin1 initialized\n"
  end
  def foo
    print "foo@DerivedMixin1 called\n"
  end
  def bar
    print "bar@DerivedMixin1 called\n"
  end
end

module DerivedMixin2
  include BaseMixin
  def initialize
    super
    print "DerivedMixin2 initialized\n"
  end
  def foo
    print "foo@DerivedMixin2 called\n"
  end
  def bar
    print "bar@DerivedMixin2 called\n"
  end
end

class Base
  include DerivedMixin1
  include DerivedMixin2
  def initialize
    super
    print "Base initialized\n"
  end
end

class Derived < Base
  include DerivedMixin2
  include DerivedMixin1
  def initialize
    super
    print "Derived initialized\n"
  end
  def bar
    print "bar@Derived called\n"
  end
end

o = Derived.new
o.foo
o.bar
