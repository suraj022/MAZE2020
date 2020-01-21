void SOLVE() {
#ifdef DFS
#endif
}
void leftWallFollow() {
  bool lw = (LEFTDISTANCE < WALLDISTANCE and LEFTDISTANCE > 0) ? true : false;
  bool fw = (FRONTDISTANCE < WALLDISTANCE and FRONTDISTANCE >0) ? true : false;
  bool rw = (RIGHTDISTANCE < WALLDISTANCE and RIGHTDISTANCE >0) ? true : false;

  if (!lw and !fw and !rw) {        //no wall
    //turn left
    turnLeft();
  } else if (!lw and !fw and rw) {   //wall on right
    //turn left and back align
    turnLeft();
#ifdef BACKALIGN
    backAlign();
#endif
  } else if (!lw and fw and !rw) {   //wall on front
    //turn left
    turnLeft();
  } else if (!lw and fw and rw) {    //wall on right and front
    //turn left and back align
    turnLeft();
#ifdef BACKALIGN
    backAlign();
#endif
  } else if (lw and !fw and !rw) {   //wall on left
    //move straight.. nothing to be done here
  } else if (lw and !fw and rw) {    //wall on left and right
    //move straight.. nothing to be done here
  } else if (lw and fw and !rw) {    //wall on left and front
    //turn right
    turnRight();
#ifdef BACKALIGN
    backAlign();
#endif
  } else if (lw and fw and rw) {     //wall on left, front and right
    //turn right twice or u-turn
    //maxCountCheck();
    uturn();
    delay(200);
#ifdef BACKALIGN
    backAlign();
#endif
  }
}


void rightWallFollow() {
}


void DFS() {
}
