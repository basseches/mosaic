#include <TFT_eSPI.h> /* Graphics and font library for ST7735 driver chip */

char *nouns[] = {
  "pseudorandomness", "the uptown train", "love", "the sea", "honesty",
  "dissonance", "anatomy", "memorization", "procrastination", "art",
  "distance", "the tv static", "the narrative", "our home", "instability",
  "the bridge of her nose", "today's paper", "a good book", "success",
  "that particular deep shade of blue", "a dream", "vocabulary", "life",
  "the nostalgia", "the sun", "october", "styrofoam", "that soft aquamarine",
  "my stream of consciousness", "satisfaction", "fragmentation", "affection",
  "the american dream", "fake poetry", "vermillion", "that dialogue",
  "that creature comfort", "the metronome", "autonomy", "that parenthetical",
  "that detail", "the writing on the walls", "that methodology", "the evening",
  "the last word", "a sentimental aside", "calmness", "chaos", "the aftermath",
  "the smell that accompanies recent rain", "suburbia", "a slow waltz",
  "the breath of the wind", "a soft veil over reality", "the weathered brick"
};

char *modifiers[] = {
  "logical", "strange", "odd", "anachronistic", "fair", "notable",
  "ok", "awkward", "a litmus test", "ironic", "sympathetic", "a little silly",
  "kaleidoscopic", "insidious", "gentle", "a long way off", "stupid",
  "amaranthine", "stateful", "idiomatic", "still", "mediocre", "diverting",
  "too harsh and too bright", "fitting", "crystalline", "dedicated",
  "anodyne", "impervious", "irrational", "an attempt", "broken", "agitated",
  "discordant", "sensible", "selfish", "cataclysmic", "vapid", "obscure",
  "the same as everything else", "turbulent", "rhythmic", "juvenile",
  "in a sorry state", "lonely", "generous", "languid", "ambitious",
  "curious", "accurate", "stylistic", "taken for granted", "ridiculous",
  "presupposed", "remarkable", "tangible", "unfinished", "generative",
  "the most forgiving thing", "not very interesting, if you ask me",
  "proverbial", "impossibly difficult", "not that revolutionary"
};

char *starters[] = {
  "you're looking for", "it's only", "there's nothing wrong with",
  "i don't mind", "it'll end with", "you should try indulging",
  "i don't think much about", "the problem is", "i've never wanted",
  "you worry too much about", "don't lose yourself in the pursuit of"
};

#define NOUNS_SIZE sizeof(nouns) / sizeof(char *)
#define MODS_SIZE sizeof(modifiers) / sizeof(char *)
#define STARTERS_SIZE sizeof(starters) / sizeof(char *)

#define BGCOLOR TFT_BLACK
#define TEXTCOLOR TFT_WHITE
#define TEXTSIZE 2
#define WAIT 500

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
char buf[4096];
int textpos = (tft.height() - 40) / 2;
char *space = " ";
char *period = ". ";

/*
 * Add some text to the global buffer, making sure that we don't write into
 * uninitialized (OOB) memory.
 */
int add_fragment(char *fragment)
{
  if ((strlen(buf) + strlen(fragment)) >= sizeof(buf))
    return 1;
  strcat(buf, fragment);
  return 0;
}

/*
 * Add a clause of the form "___ is ___" to the global buffer.
 */
int clause()
{
  if (add_fragment(nouns[random(NOUNS_SIZE)])) return 1;
  if (add_fragment(" is ")) return 1;
  if (add_fragment(modifiers[random(MODS_SIZE)])) return 1; 
  return 0;
}

/*
 * Add a clause with some sentence starter to the global buffer.
 */
int clause_with_starter()
{
  if (add_fragment(starters[random(STARTERS_SIZE)])) return 1;
  if (add_fragment(space)) return 1;
  if (add_fragment(nouns[random(NOUNS_SIZE)])) return 1;
  return 0;
}

/*
 * Reset the screen (after each iteration of text scrolling loop).
 */
void reset()
{
  tft.fillScreen(BGCOLOR);
  tft.setTextColor(TEXTCOLOR);
  tft.setCursor(0, 0, TEXTSIZE);
}

/*
 * Scroll some text across the screen.
 */
void scroll_text()
{
  // Iterate over all the characters in the string, redrawing it each time.
  for (int i = 0; i < strlen(buf); i++) {
    reset();
    tft.drawString(buf + i, 0, textpos, 2);
    delay(100);
  }
}

void setup(void)
{
  tft.init();
  // I changed this to 4 last-minute for our installation, but more
  // text is displayed with a horizontal rotation (i.e., 1 or 3).
  tft.setRotation(4);
  tft.setSwapBytes(true);
  tft.setTextSize(TEXTSIZE);
  // seed the rng with the input from an unused pin
  randomSeed(analogRead(0));
}

void loop()
{
  while (1) {
    // Add a clause to the buffer. If we've run out of space, break.
    if (random(2)) {
      if (clause()) break;
    } else {
      if (clause_with_starter()) break;
    }

    // End sentence (with probability 2/3) or connect clauses (1/3).
    if (random(3)) {
      if (add_fragment(period)) break;
    } else {
      if (random(2)) {
        if (add_fragment(", and ")) break;
      } else {
        if (add_fragment(", but ")) break;
      } 
    }
  }

  // Once the buffer is full (i.e. around 4096 characters), scroll the text
  // across the screen.
  scroll_text();

  // Start over again by null-terminating at the zeroth index, and wait a bit.
  buf[0] = 0;
  delay(WAIT);
}
