difference() {
  polygon(points=[
    [-35/2, 0],
    [35/2, 0],
    [1.5, 240],
    [-1.5, 240]
  ]);
  
  translate([0, 30/2, 0]) circle(r=1.5, $fn=36);
  translate([0, 30/2, 0]) {
    for (a = [45, 135, 225, 315]) {
      rotate([0, 0, a]) translate([7.5, 0, 0]) circle(r=1.6, $fn=36);
    }
  }
}
