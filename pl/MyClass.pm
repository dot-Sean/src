ackage MyClass;

sub new {
  my $class = shift;
  my $self = {};
  my ($real, $imag) = @_;
  $self->{"real"} = $real;
  $$self{"imag"} = $imag;
  return bless $self, $class;
}

sub show {
  my $self = shift;
  print "MyClass:\n";
  printf "%d + %d i\n", $$self{"real"}, $self->{"imag"};
}

sub hoge {
  my $self = shift;
  print "hoge\n";
}

1;
