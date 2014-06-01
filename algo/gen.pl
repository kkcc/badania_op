for($i=0; $i<$ARGV[0]; $i++){
    while( 1 ) {
        $x = int( rand( $ARGV[1])) + 1; 
        last if !$h{ $x };
        $h{ $x } = 1;
    }
    print $x.' ';
}
