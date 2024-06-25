// La broche numérique 3 est reliée au Bouton. On lui donne le nom Bouton.
int Bouton = 3;
// Déclaration variable EtatBouton qui va servir à stocker une valeur au format bool soit LOW ou HIGH.
bool EtatBouton;

void setup() {
  // Ouvre le port série à 9600 bps.
  Serial.begin(9600);
  // Faire de la broche du Bouton une entrée.
  pinMode(Bouton, INPUT);
}

void loop() {
  // Lit la broche d'entrée du Bouton et stock ça valeur dans EtatBouton
  EtatBouton = digitalRead(Bouton);
  // Si EtatBouton == HIGH
  if (EtatBouton == HIGH)
  {
    // Imprime "not pressed" dans le moniteur série
    // puis ajoute le retour à la ligne avec "println"
    Serial.println("not pressed");
  }
  // Sinon
  else {
    // Imprime "On" dans le serial monitor
    // puis ajoute le retour à la ligne avec "println"
    Serial.println("pressed");
  }
  // attend 1 milliseconde.
  delay(1);
}