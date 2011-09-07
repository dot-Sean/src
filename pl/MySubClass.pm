package MySubClass;

use MyClass;

# Necessary to find class methods which are defined in the base class
@ISA = qw(MyClass);

sub new {
  my $class = shift;
  my $self = new MyClass(@_);
  return bless $self, $class;
}

sub show {
  my $self = shift;
  print "MySubClass:\n";
  MyClass::show($self);
}

1;
