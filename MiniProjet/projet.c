#include "projet.h"

static char *CitationsSeneque[] = {
"Le travail est l'aliment des âmes nobles.",
"C'est pendant l'orage qu'on connait le pilote.",
"Toute la vie n'est qu'un voyage vers la mort.",
"Hâte toi de bien vivre et songe que chaque jour est à lui seul une vie.",
"Je préfère modérer mes joies que réprimer mes douleurs.",
"Il ne vaut mieux ne pas commencer que de cesser",
"Un grand exemple ne nait que de la mauvaise fortune.",
"Il est vaincu sans gloire celui qui est vaincu sans péril.",
"La parole reflète l'âme.",
"A quoi perd-on la plus grand partie de sa vie ? à différer.",
"On est nulle part quand on est partout.",
"Pendant qu'on la diffère, la vie passe en courant.",
"Ils vomissent pour manger, ils mangent pour vomir.",
"L'erreur n'est pas un crime."};


Snare SnareColorUpdate(Snare snare)
{
    if (snare.state == SNARE_START) snare.color = LIGHTGRAY;
    if (snare.state == SNARE_LOADING) snare.color = PURPLE;
    if (snare.state == SNARE_CHARGED) snare.color = DARKPURPLE;
    return snare;
}

bool SnareAlreadyAtPosition(Liste snares, Vector2 position)
{
    Liste currentList = snares;
    while (currentList != NULL)
    {
        if ((currentList->val.position.x == position.x) && (currentList->val.position.y == position.y)) return true;
        currentList = currentList->suiv;
    }   
    return false;
}

bool SnareCollision(Liste snares, Vector2 position)
{
    Liste currentList = snares;
    while (currentList != NULL)
    {   
        if (currentList->val.state == SNARE_CHARGED)
        {
            if ((currentList->val.position.x == position.x) && (currentList->val.position.y == position.y)) return true;
            
        }
        currentList = currentList->suiv;
    }   
    return false;
}

Snare SnareInit(Liste snares, Snare snare, Vector2 fruitPosition)
{
    Vector2 offset = {0};

    offset.x = GetScreenWidth() % SQUARE_SIZE;
    offset.y = GetScreenHeight() % SQUARE_SIZE;

    snare.size = (Vector2) { SQUARE_SIZE, SQUARE_SIZE };    

    snare.active = true;

    snare.state = SNARE_START;

    snare.nSeconds = 0;

    snare.color = LIGHTGRAY;

    snare.position = (Vector2){GetRandomValue(0, (GetScreenWidth() / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2, GetRandomValue(0, (GetScreenHeight() / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2};

    while (SnareAlreadyAtPosition(snares, snare.position) || ((fruitPosition.x == snare.position.x) && (fruitPosition.y == snare.position.y)))
    {
        snare.position = (Vector2){GetRandomValue(0, (GetScreenWidth() / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.x / 2, GetRandomValue(0, (GetScreenHeight() / SQUARE_SIZE) - 1) * SQUARE_SIZE + offset.y / 2};
    }

    return snare;
}

Liste SnareStateIteration(Liste snares, unsigned int nbCalls)
{
    Liste currentList = snares;
    while (currentList != NULL)
    {
        if (currentList->val.state != SNARE_CHARGED)
        {
            currentList->val.state++;
            currentList->val = SnareColorUpdate(currentList->val);
        }
       
        currentList = currentList->suiv;
    }
    return snares;
}

Liste UpdateSnares(Liste snares, unsigned int waitForNext, unsigned int lifeSpanSnare, Vector2 fruitPosition)
{
    static unsigned int nbCalls = 1;

    Snare snare = { 0 };

    if (nbCalls % (60 * waitForNext) == 0)
    {
        SnareStateIteration(snares, nbCalls);

        snare = SnareInit(snares, snare, fruitPosition);

        snare.nSeconds = nbCalls / 60;

        snares = ajoutFin(snare ,snares);
    }

    if (nbCalls == 60) 
        nbCalls = 60;

    if (((nbCalls / 60) - snares->val.nSeconds) == lifeSpanSnare)
    {
        retirePremierElement(snares);
    }

    nbCalls++;
    return snares;
}

void DrawSnares(Liste snares)
{
    Liste currentList = snares;
    while (currentList != NULL)
    {
        DrawRectangleV(currentList->val.position, currentList->val.size, currentList->val.color);
        currentList = currentList->suiv;
    }
}

void IfCollisionSendCitation(GAME_SENEQUE *GameSeneque, int currentFrameNumber)
{
    GameSeneque->isCitation = true;
    GameSeneque->LastCitationFrame = currentFrameNumber;
}

void displayCitationForSeconds(GAME_SENEQUE *GameSeneque, int seconds, int currentFrameNumber)
{
    if ((currentFrameNumber - GameSeneque->LastCitationFrame) > (60 * seconds))
    {
        GameSeneque->isCitation = false;
        GameSeneque->indexCitation = GetRandomValue(0, (sizeof(CitationsSeneque) / sizeof(CitationsSeneque[0])));
    }
}

void DrawSenequeHead(GAME_SENEQUE *GameSeneque, Vector2 SnakeHeadPosition)
{
    DrawTexture(GameSeneque->SenequeHeadImage, SnakeHeadPosition.x, SnakeHeadPosition.y, WHITE);

    if (GameSeneque->isCitation == true)
    {
        DrawText(CitationsSeneque[GameSeneque->indexCitation], GetScreenWidth() / 2 - MeasureText(CitationsSeneque[GameSeneque->indexCitation], 21) / 2, GetScreenHeight() / 2 - 21, 23, DARKBLUE);
    }
}

bool estVide(Liste l) {
	return l == NULL;
}

Liste creer(Element v){
	Liste l = malloc(sizeof(Cellule));
	if (l!= NULL)
	{
		l->val = v;
		l->suiv = NULL;
	}
	return l;
}

Liste ajoutTete(Element v, Liste l) {
	Liste newList = malloc(sizeof(Cellule));
	if (newList != NULL)
	{
		newList->suiv = l;
		newList->val = v;
	}
	return newList;
}

void detruire(Liste l) 
{
	Liste nextList = NULL;
	Liste currentList = l;

	if (!(estVide(l)))
	{
		while (currentList != NULL) 
		{
			nextList = currentList->suiv;
			free(currentList);
			currentList = nextList;
		}
	}
}

Liste ajoutFin(Element v, Liste l) 
{
	Liste lastElement = l;
	Liste newList = malloc(sizeof(Cellule));
	if (newList != NULL)
	{
		while (lastElement->suiv != NULL){
			lastElement = lastElement->suiv;
		}
	}
	lastElement->suiv = newList;
	newList->val = v;
	newList->suiv = NULL;
	return l;
}

Liste retirePremierElement(Liste l)
{
    Liste premierElement = { 0 };
	if (!estVide(l))
    {
        premierElement = l;
        l = l->suiv;
        free(premierElement);
        premierElement = NULL;
    }
    return l;
}

Liste InitProjetAddOn(GAME_SENEQUE *gameSeneque, Liste snares)
{
    Image TempImage = { 0 };
    Snare snare = { 0 };

    TempImage = LoadImage("assets/seneque.png");
    ImageResize(&TempImage, SQUARE_SIZE, SQUARE_SIZE);
    gameSeneque->SenequeHeadImage = LoadTextureFromImage(TempImage);
    UnloadImage(TempImage);
    gameSeneque->isCitation = false;

    snare = SnareInit(snares, snare, (Vector2) {0,0});
    snares = creer(snare);
    return snares;
}

void CloseProjetAddOn(GAME_SENEQUE *gameSeneque, Liste snares)
{
    UnloadTexture(gameSeneque->SenequeHeadImage);

    detruire(snares);
}