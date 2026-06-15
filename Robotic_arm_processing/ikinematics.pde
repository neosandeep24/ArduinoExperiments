float F = 50;
float T = 70;

void IK() {
  float X = posX;
  float Y = posY;
  float Z = posZ;

  float L   = sqrt(Y*Y + X*X);
  if (L < 0.001) L = 0.001;     // FIX: guard atan2(0,0) singularity
  float dia = sqrt(Z*Z + L*L);
  if (dia < 0.001) dia = 0.001; // FIX: guard degenerate reach

  float a1 = constrain((T*T - F*F - dia*dia) / (-2*F*dia), -1, 1);
  float a2 = constrain((dia*dia - T*T - F*F) / (-2*F*T),   -1, 1);

  alpha = PI/2 - (atan2(L, Z) + acos(a1));
  beta  = -PI  + acos(a2);
  gamma = atan2(X, Y);   // full ±PI range — negative X now reaches correctly
}

void writePos() {
  IK();

  // FIX: map to 0-180 servo range before sending
  int sBase  = constrain((int) map(gamma,  -PI,   PI,   0, 180), 0, 180);
  int sAlpha = constrain((int) map(alpha,  -PI/2, PI/2, 0, 180), 0, 180);
  int sBeta  = constrain((int) map(beta,   -PI,   0,    0, 180), 0, 180);

  myPort.write(sBase + "," + sAlpha + "," + sBeta + "\n");
}
