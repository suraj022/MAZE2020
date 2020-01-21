void indicateEndOfTileRun() {
  digitalWrite(buzzPin, HIGH);
  delay(100);
  digitalWrite(buzzPin, LOW);
  delay(100);
}
