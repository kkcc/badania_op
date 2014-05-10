#!/usr/bin/perl
$how_many = $ARGV[0] || 25;


$nice_sum = 10000;
@out;
%map;

for( $i=0; $i<$how_many/2; $i++){

    do{ 
        $x1 = int( rand($nice_sum) ) ; #not to random 0
        $x2 = $nice_sum-$x1;
    
    }while( exists $map{ $x1 } or  exists $map{ $x2 });
    
    

    $map{ $x1 } = 1;
    $map{ $x2 } = 1; 
    
    push @out, ($x1, $x2);

}

push(@out, $nice_sum) if $i != $how_many/2;

$, = ' ';
print @out;
