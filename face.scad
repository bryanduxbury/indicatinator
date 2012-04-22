h=300;
w=600;

difference() {
  square(size=[w, h], center=true);
  
  // corner mounting holes
  for (a=[0, 180]) {
    rotate([0, 0, a]) {
      translate([w/2 - 10, h/2 - 10]) circle(r=2.5);
      translate([w/2 - 10, -h/2 + 10]) circle(r=2.5);
    }
  }
  
  // servo
  translate([0, -h/2 + 55.5/2 + 5, 0]) {
    // central servo hole
    square(size=[20, 40], center=true);
    
    // keyed tab slots
    translate([0, -40.5/2 - 2, 0]) square(size=[2.2, 4.7], center=true);
    translate([0, 40.5/2 + 2, 0]) square(size=[2.2, 4.7], center=true);
    
    // mounting holes
    for (dirx = [1, -1]) {
      for (diry = [1, -1]) {
        translate([dirx*5, diry*50.5/2, 0]) circle(r=1.6, $fn=36);
      }
    }
  }
  
  // adjustment switches
  translate([w/2 - 3.15 * 25.4 - 25, h/2 - 10 - 4000/1000*25.4/2, 0]) {
    union() {
      circle(r=10.3/2);
      translate([0, -10.3/2, 0]) square(size=[1.8, 2], center=true);
    }
  }

  translate([w/2 - 3.15 * 25.4 - 50, h/2 - 10 - 4000/1000*25.4/2, 0]) {
    union() {
      circle(r=10.3/2);
      translate([0, -10.3/2, 0]) square(size=[1.8, 2], center=true);
    }
  }
  
  
  // arduino
  translate([w/2 - 10 - 3.15*25.4/2, h/2 - 20 - 4000/1000*25.4/2, 0]) rotate([0, 0, 90]) translate([-4000/1000*25.4/2, -2100/1000*25.4/2, 0]) {
    translate([550/1000*25.4, 100/1000*25.4, 0]) circle(r=1.6);
    translate([600/1000*25.4, 2000/1000*25.4, 0]) circle(r=1.6);
    translate([2600/1000*25.4, 1400/1000*25.4, 0]) circle(r=1.6);
    translate([2600/1000*25.4, 300/1000*25.4, 0]) circle(r=1.6);
    translate([3550/1000*25.4, 2000/1000*25.4, 0]) circle(r=1.6);
    translate([3800/1000*25.4, 100/1000*25.4, 0]) circle(r=1.6);
  }
  
  // led holes
  translate([0, -h/2 + 55.5/2 + 5 + 40.5/2 - 10.4, 0]) {
    for (i=[0:39]) {
      rotate([0, 0, -180/40 / 2 + -180/40 * i]) translate([-w/2 + 60, 0, 0]) circle(r=2.6); 
    }
  }
}
