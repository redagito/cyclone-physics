#include "IceMeltingDemo.h"

#include <cstdio>
#include <GL/freeglut.h>

#define RECORD_AT_START false
#define FORCED_AT_START true
#define FORCED_DURATION 0.016f

// simulation properties
#define ICE_DIST 0.2f // distance between molecules - don't go below 0.2f
#define CUBE_DEPTH 4 // anything over 8 takes too long to render
#define MOLECULE_DRAW_SCALE 1.4f // values of 0.5f thru 3.0f look best
#define DRAW_BONDS false
#define BOND_CONDUCTIVITY 0.001f // lower numbers = less conductivity, default: 0.001f
#define BASE_MASS 1
#define BASE_GRAVITY cyclone::Vector3( 0, -1.0f, 0 ) // cyclone::Vector3::GRAVITY is too strong for Euler

// window properties
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 385

// static properties - don't change
#define ICE_CROSS_DIST sqrt( 2.0f ) * ICE_DIST

// CONSTRUCTOR
IceMeltingDemo::IceMeltingDemo(const unsigned depth)
	:
	cubeDepth(depth),
	bondCount(2 * cubeDepth * cubeDepth * (cubeDepth - 1)
		+ cubeDepth * cubeDepth * (cubeDepth - 1)
		+ 3 * cubeDepth * (cubeDepth - 1) * (cubeDepth - 1)),
	moleculeCount(depth* depth* depth),
	world((depth* depth* depth) * 10)
{
	// initialize non-const variables
	molecules = new Molecule[moleculeCount];
	moleculesOrig = new Molecule[moleculeCount];
	bonds = new Bond[bondCount];
	bondsOrig = new Bond[bondCount];
	spaceFlag = false;
	zeroFlag = FORCED_AT_START;
	forcedDuration = FORCED_DURATION;

	const unsigned slice = cubeDepth * cubeDepth; // horizontal slice
	const unsigned c = cubeDepth - 1;

	// add molecules to world
	for (unsigned i = 0; i < moleculeCount; i++) world.getParticles().push_back(molecules + i);
	groundContactGenerator_.init(&world.getParticles());
	world.getContactGenerators().push_back(&groundContactGenerator_);

	int count = 0;
	for (unsigned i = 0; i < cubeDepth; i++) {
		for (unsigned j = 0; j < cubeDepth; j++) {
			for (unsigned k = 0; k < cubeDepth; k++) {
				molecules[count].setSize(MOLECULE_DRAW_SCALE * cubeDepth * ICE_DIST * 0.08f);
				molecules[count].setPosition(ICE_DIST * k, ICE_DIST * i, ICE_DIST * j);
				molecules[count].setMass(BASE_MASS);
				molecules[count].setVelocity(0, 0, 0);
				molecules[count].setDamping(0.9f);
				molecules[count].setAcceleration(BASE_GRAVITY);
				molecules[count++].clearAccumulator();
			}
		}
	}

	for (unsigned i = 0; i < moleculeCount; i++)
		moleculesOrig[i] = molecules[i]; // store original state

	count = 0;
	unsigned rodNumber = 0;
	for (unsigned i = 0; i < cubeDepth; i++) {
		for (unsigned j = 0; j < cubeDepth; j++) {
			for (unsigned k = 1; k < cubeDepth; k++) {
				// link all molecules in row
				bonds[rodNumber].particle[0] = &molecules[count];
				bonds[rodNumber].particle[1] = &molecules[count + 1];
				bonds[rodNumber].length = ICE_DIST;
				rodNumber++;
				count++;
				if (rodNumber >= bondCount) break;
			}

			if (j != cubeDepth - 1) {
				unsigned x = 1;
				int y = c;

				// j connector
				for (unsigned k = cubeDepth; k > 0; k--) {
					bonds[rodNumber].particle[0] = &molecules[count - y];
					bonds[rodNumber].particle[1] = &molecules[count + x];
					bonds[rodNumber].length = ICE_DIST;
					rodNumber++;
					if (rodNumber >= bondCount) break;
					x++;
					y--;
				}

				// back cross down
				for (unsigned k = 0; k < c; k++) {
					bonds[rodNumber].particle[0] = &molecules[count - k];
					bonds[rodNumber].particle[1] = &molecules[count - k + c];
					bonds[rodNumber].length = ICE_CROSS_DIST;
					rodNumber++;
				}
			}
			count++;
		}

		int p, q;

		if (i != cubeDepth - 1) {
			p = 0;
			q = slice;

			for (unsigned j = 0; j < slice; j++) {
				bonds[rodNumber].particle[0] = &molecules[count + p];
				bonds[rodNumber].particle[1] = &molecules[count - q];
				bonds[rodNumber].length = ICE_DIST;
				rodNumber++;
				if (rodNumber >= bondCount) break;
				p++;
				q--;
			}

			for (unsigned j = 0; j < slice; j++) { // crossing the fronts, not last in row
				if (j % cubeDepth) {
					// forward cross
					bonds[rodNumber].particle[0] = &molecules[count - 1 - j];
					bonds[rodNumber].particle[1] = &molecules[count - j + slice];
					bonds[rodNumber].length = ICE_CROSS_DIST;
					rodNumber++;
				}

				// crossing the sides
				if ((j / cubeDepth) > 0) {
					bonds[rodNumber].particle[0] = &molecules[count - 1 - j];
					bonds[rodNumber].particle[1] = &molecules[count - 1 - j + slice + cubeDepth];
					bonds[rodNumber].length = ICE_CROSS_DIST;
					rodNumber++;
				}
			}
		}
	}

	for (unsigned i = 0; i < bondCount; i++) {
		bonds[i].setConductivity(BOND_CONDUCTIVITY); // set all bonds to have the same conductivity
		bondsOrig[i] = bonds[i]; // store original state
		world.getContactGenerators().push_back(&bonds[i]);
	}

	origContactGenerators = world.getContactGenerators(); // store original state
}

IceMeltingDemo::~IceMeltingDemo() 
{
	if (bonds) delete[] bonds;
	if (bondsOrig) delete[] bondsOrig;
	if (molecules) delete[] molecules;
	if (moleculesOrig) delete[] moleculesOrig;
}

void IceMeltingDemo::initGraphics()
{
	glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT); // window size
	glutPositionWindow(20, 20); // window position

	glClearColor(0.9f, 0.95f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	setView();
}

void IceMeltingDemo::update()
{
	world.startFrame();

	duration = (float)TimingData::get().lastFrameDuration * 0.001f;
	if (duration <= 0.0f) return;

	if (zeroFlag)
		duration = forcedDuration; 

	auto* cgs = &world.getContactGenerators();
	cyclone::ParticleWorld::ContactGenerators::iterator g;
	for (unsigned i = 0; i < bondCount; i++) {
		g = std::find(cgs->begin(), cgs->end(), &bonds[i]);
		if (g == cgs->end()) { 
			if (bonds[i].getState()) 
				cgs->push_back(&bonds[i]);
		}
		else { 
			if (!bonds[i].getState()) 
				cgs->erase(g);
		}
	}

	world.runPhysics(duration);
	Application::update();

	for (unsigned i = 0; i < moleculeCount; i++)
		if (molecules[i].getState()) molecules[i].update(duration);

	for (unsigned i = 0; i < bondCount; i++)
		if (bonds[i].getState()) bonds[i].update(duration);
}

void IceMeltingDemo::display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	float zoom = cubeDepth * ICE_DIST * 1.60f;
	gluLookAt(zoom, (zoom * 0.75f), zoom, 0.0, ICE_DIST, 0.0, 0.0, 1.0, 0.0);

	for (unsigned i = 0; i < moleculeCount; i++)
		if (molecules[i].getState()) molecules[i].draw();

	if (DRAW_BONDS)
		for (unsigned i = 0; i < bondCount; i++)
			if (bonds[i].getState()) bonds[i].draw();

	// this HUD will be captured in screenshots
	char hud_top[50];
	sprintf_s(hud_top, "Delta Time:  %f [%s] Frame: %d", duration, (zeroFlag ? "FORCED" : "NORMAL"), (int)TimingData::get().frameNumber);
	glColor3f(0, 0, 0);
	renderText(10.0f, (height - 20.0f), hud_top);
}

// detect key press
void IceMeltingDemo::key(unsigned char key) 
{
	switch (key) {
	case ' ':
		for (unsigned i = 0; i < moleculeCount; i++) {
			Molecule& m = molecules[i];

			if (spaceFlag)
				m.setAcceleration(BASE_GRAVITY);
			else
				m.setAcceleration(cyclone::Vector3(0, (i % 2), 0));
		}
		spaceFlag = (spaceFlag ? false : true);
		break;
	case '1':
		spaceFlag = false;
		for (unsigned i = 0; i < moleculeCount; i++) molecules[i] = moleculesOrig[i]; // restore original state
		for (unsigned i = 0; i < bondCount; i++) bonds[i] = bondsOrig[i]; // restore original state
		world.getContactGenerators().assign(origContactGenerators.begin(), origContactGenerators.end()); // restore original state
		break;
	case '9':
		forcedDuration = FORCED_DURATION;
		break;
	case '0': 
		zeroFlag = (zeroFlag ? false : true);
		break;
	case '=': 
		forcedDuration += 0.001f;
		break;
	case '-':
		if (forcedDuration > 0.001f)
			forcedDuration -= 0.001f;
		else
			forcedDuration -= 0.0001f; // decrement slower

		if (forcedDuration <= 0.0f) forcedDuration = 0.0001f; // avoid zero duration
		break;
	case '5':
		unsigned i = 9;
		bonds[i].particle[0] = &molecules[rand() % moleculeCount];

		dynamic_cast<Molecule*>(bonds[i].particle[0])->setTemp(0); 
		dynamic_cast<Molecule*>(bonds[i].particle[1])->setTemp(0.5f); 
		bonds[i].setState(1);
		bonds[i].setTemp(0); 
		break;
	}
}

// returns program title
const char* IceMeltingDemo::getTitle()
{
	return "Cyclone > Ice Melt";
}

// create an application object
Application* getApplication()
{
	return new IceMeltingDemo(CUBE_DEPTH);
}