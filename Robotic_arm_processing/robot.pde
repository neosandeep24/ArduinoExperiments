import processing.serial.*;
Serial myPort;
PShape base, shoulder, upArm, loArm, end;
float rotX, rotY;
float posX = 0;   // FIX: was 1
float posY = 50;
float posZ = 50;
float alpha, beta, gamma;
float[] Xsphere = new float[99];
float[] Ysphere = new float[99];
float[] Zsphere = new float[99];

int joyX = 512;
int joyY = 512;
int selectedAxis = 0;
boolean oldSW = false;
String[] axisNames = {"X (left/right)", "Y (fwd/back)", "Z (up/down)"};

void setup() {
  size(1200, 800, OPENGL);
  base     = loadShape("r5.obj");
  shoulder = loadShape("r1.obj");
  upArm    = loadShape("r2.obj");
  loArm    = loadShape("r3.obj");
  end      = loadShape("r4.obj");
  shoulder.disableStyle();
  upArm.disableStyle();
  loArm.disableStyle();
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  writePos();
  background(32);
  smooth();
  lights();
  directionalLight(51, 102, 126, -1, 0, 0);

  for (int i = 0; i < Xsphere.length - 1; i++) {
    Xsphere[i] = Xsphere[i + 1];
    Ysphere[i] = Ysphere[i + 1];
    Zsphere[i] = Zsphere[i + 1];
  }
  Xsphere[Xsphere.length - 1] = posX;
  Ysphere[Ysphere.length - 1] = posY;
  Zsphere[Zsphere.length - 1] = posZ;

  noStroke();
  translate(width / 2, height / 2);
  rotateX(rotX);
  rotateY(-rotY);
  scale(-4);

  for (int i = 0; i < Xsphere.length; i++) {
    pushMatrix();
    translate(-Ysphere[i], -Zsphere[i] - 11, -Xsphere[i]);
    fill(#000000, 25);
    sphere(0);
    popMatrix();
  }

  fill(#FFE308);
  translate(0, -40, 0);
  shape(base);
  translate(0, 4, 0);
  rotateY(gamma);
  shape(shoulder);
  translate(0, 25, 0);
  rotateY(PI);
  rotateX(alpha);
  shape(upArm);
  translate(0, 0, 50);
  rotateY(PI);
  rotateX(beta);
  shape(loArm);
  translate(0, 0, -50);
  rotateY(PI);
  shape(end);

  drawHUD();
}

void drawHUD() {
  hint(DISABLE_DEPTH_TEST);
  camera();
  noLights();
  fill(255, 255, 255, 180);
  textSize(14);
  text("Axis: " + axisNames[selectedAxis], 20, 30);
  text("X: " + nf(posX,1,1) + "  Y: " + nf(posY,1,1) + "  Z: " + nf(posZ,1,1), 20, 50);
  hint(ENABLE_DEPTH_TEST);
}

void mouseDragged() {
  rotY -= (mouseX - pmouseX) * 0.01;
  rotX -= (mouseY - pmouseY) * 0.01;
}

void serialEvent(Serial p) {
  String data = p.readStringUntil('\n');
  if (data != null) {
    String v[] = split(trim(data), ',');
    if (v.length == 3) {
      joyX = int(v[0]);
      joyY = int(v[1]);
      boolean sw = int(v[2]) == 0;
      if (sw && !oldSW) {
        selectedAxis = (selectedAxis + 1) % 3;
      }
      oldSW = sw;
      controlPosition();
    }
  }
}

void controlPosition() {
  float speed = 1.5;
  float deadZone = 80;
  float jx = joyX - 512;
  float jy = joyY - 512;

  // FIX: remap active range only — smooth response from dead zone edge
  float x = (abs(jx) < deadZone) ? 0 : map(abs(jx), deadZone, 512, 0, speed) * sign(jx);
  float y = (abs(jy) < deadZone) ? 0 : map(abs(jy), deadZone, 512, 0, speed) * sign(jy);

  if (selectedAxis == 0)      posX += x;
  else if (selectedAxis == 1) posY += x;
  else if (selectedAxis == 2) posZ -= y;

  posX = constrain(posX, -80, 80);
  posY = constrain(posY, 10, 120);
  posZ = constrain(posZ, 10, 100);
}

float sign(float v) { return (v > 0) ? 1 : (v < 0) ? -1 : 0; }






//PShape base, shoulder, upArm, loArm, end;
//float rotX, rotY;
//float posX=1, posY=50, posZ=50;
//float alpha, beta, gamma;


//float[] Xsphere = new float[99];
//float[] Ysphere = new float[99];
//float[] Zsphere = new float[99];

//void setup(){
//    size(1200, 800, OPENGL);
    
//    base = loadShape("r5.obj");
//    shoulder = loadShape("r1.obj");
//    upArm = loadShape("r2.obj");
//    loArm = loadShape("r3.obj");
//    end = loadShape("r4.obj");
    
//    shoulder.disableStyle();
//    upArm.disableStyle();
//    loArm.disableStyle(); 
//}

//void draw(){ 
//   writePos();
//   background(32);
//   smooth();
//   lights(); 
//   directionalLight(51, 102, 126, -1, 0, 0);
    
//    for (int i=0; i< Xsphere.length - 1; i++) {
//    Xsphere[i] = Xsphere[i + 1];
//    Ysphere[i] = Ysphere[i + 1];
//    Zsphere[i] = Zsphere[i + 1];
//    }
    
//    Xsphere[Xsphere.length - 1] = posX;
//    Ysphere[Ysphere.length - 1] = posY;
//    Zsphere[Zsphere.length - 1] = posZ;
   
//   noStroke();
   
//   translate(width/2,height/2);
//   rotateX(rotX);
//   rotateY(-rotY);
//   scale(-4);
   
//   for (int i=0; i < Xsphere.length; i++) {
//     pushMatrix();
//     translate(-Ysphere[i], -Zsphere[i]-11, -Xsphere[i]);
//     fill (#D003FF, 25);
//     sphere (float(i) / 20);
//     popMatrix();
//    }
    
//   fill(#FFE308);  
//   translate(0,-40,0);   
//     shape(base);
     
//   translate(0, 4, 0);
//   rotateY(gamma);
//     shape(shoulder);
      
//   translate(0, 25, 0);
//   rotateY(PI);
//   rotateX(alpha);
//     shape(upArm);
      
//   translate(0, 0, 50);
//   rotateY(PI);
//   rotateX(beta);
//     shape(loArm);
      
//   translate(0, 0, -50);
//   rotateY(PI);
//     shape(end);
//}

//void mouseDragged(){
//    rotY -= (mouseX - pmouseX) * 0.01;
//    rotX -= (mouseY - pmouseY) * 0.01;
//}
