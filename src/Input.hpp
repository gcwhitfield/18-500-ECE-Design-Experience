#ifndef INPUT
#define INPUT

struct Input {
    enum KeyCode {
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69, 
        F = 70, 
        G = 71, 
        H = 72,
        I = 73,
        J = 74, 
        K = 75, 
        L = 76, 
        M = 77, 
        N = 78, 
        O = 79, 
        P = 80, 
        Q = 81, 
        R = 82, 
        S = 83, 
        T = 84, 
        U = 85, 
        V = 86, 
        W = 87,
        X = 88, 
        Y = 89, 
        Z = 90,
        ZERO = 48,
        ONE = 49, 
        TWO = 50,  
        THREE = 51, 
        FOUR = 52,
        FIVE = 53, 
        SIX = 54, 
        SEVEN = 55, 
        EIGHT = 56, 
        NINE = 57,
        ENTER = 257,
        LEFT_SHIFT = 340,
        RIGHT_SHIFT = 344,
        SPACE = 32,
        ESCAPE = 256
    };

    enum KeyAction {
        RELEASE = 0, // action is 0 when the user releases the button
        PRESS = 1, // action is 1 when the user presses the button for the first time
        HOLD = 2 // action is 2 when the user is holding the button for additional frames after the 
                 // first press
    };
};

#endif