//#define Launch

#ifdef Launch

class ControlHandle {
public:
	virtual void action() = 0;
};

class Jump : ControlHandle {
	virtual void action() {
		//JUMP
	}
};

class MoveForward : ControlHandle {
	virtual void action() {
		//MOVE Forward
	}
};

class MoveBack : ControlHandle {
	virtual void action() {
		//Move Back
	}
};

class MoveLeft : ControlHandle {
	virtual void action() {
		//Move Left
	}
};

class MoveRight : ControlHandle {
	virtual void action() {
		//Move Right
	}
};

class KeyCheck {
	ControlHandle* key_A;
	ControlHandle* key_B;
	ControlHandle* key_C;
	ControlHandle* key_D;

	void Keycheck(ControlHandle* key) {
		if (key_A is pressed) {
			key_A->action();
		}
		if (key_B is pressed) {
			key_B->action();
		}
	}
};

#endif Launch