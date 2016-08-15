// applekeyboard2.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <tchar.h>
#include <iostream>
#include <Interception/interception.h>

//int _tmain(int argc, _TCHAR* argv[])
//{
//
//
//	return 0;
//}

enum ScanCode
{
    SCANCODE_ESC = 0x01,
};

const InterceptionKeyStroke left_win_down = { 0x5b, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0 };
const InterceptionKeyStroke left_win_up = { 0x5b, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0 };

const InterceptionKeyStroke left_alt_down = { 0x38, INTERCEPTION_KEY_DOWN };
const InterceptionKeyStroke left_alt_up = { 0x38, INTERCEPTION_KEY_UP };

const InterceptionKeyStroke right_win_down = { 0x5c, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0 };
const InterceptionKeyStroke right_win_up = { 0x5c, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0 };

const InterceptionKeyStroke right_alt_down = { 0x38, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0 };
const InterceptionKeyStroke right_alt_up = { 0x38, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0 };

const InterceptionKeyStroke application_down = { 0x5d, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0 };
const InterceptionKeyStroke application_up = { 0x5d, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0 };

const InterceptionKeyStroke f13_down = { 0x64, INTERCEPTION_KEY_DOWN };
const InterceptionKeyStroke f13_up = { 0x64, INTERCEPTION_KEY_UP };

const InterceptionKeyStroke f14_down = { 0x65, INTERCEPTION_KEY_DOWN };
const InterceptionKeyStroke f14_up = { 0x65, INTERCEPTION_KEY_UP };

const InterceptionKeyStroke f15_down = { 0x66, INTERCEPTION_KEY_DOWN };
const InterceptionKeyStroke f15_up = { 0x66, INTERCEPTION_KEY_UP };

const InterceptionKeyStroke insert_down = { 0x52, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0 };
const InterceptionKeyStroke insert_up = { 0x52, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0 };

const InterceptionKeyStroke volume_down_down = { 0x2e, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0 };
const InterceptionKeyStroke volume_down_up = { 0x2e, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0 };

const InterceptionKeyStroke volume_up_down = { 0x30, INTERCEPTION_KEY_DOWN | INTERCEPTION_KEY_E0 };
const InterceptionKeyStroke volume_up_up = { 0x30, INTERCEPTION_KEY_UP | INTERCEPTION_KEY_E0 };


bool operator == (const InterceptionKeyStroke &first, const InterceptionKeyStroke &second)
{
    return first.code == second.code && first.state == second.state;
}

bool operator != (const InterceptionKeyStroke &first, const InterceptionKeyStroke &second)
{
    return !(first == second);
}

void substitute(InterceptionKeyStroke& stroke)
{
    if (stroke == left_alt_down) {
        stroke = left_win_down;
        return;
    }
    if (stroke == left_alt_up) {
        stroke = left_win_up;
        return;
    }

    if (stroke == left_win_down) {
        stroke = left_alt_down;
        return;
    }
    if (stroke == left_win_up) {
        stroke = left_alt_up;
        return;
    }

    if (stroke == right_alt_down) {
        stroke = application_down;
        return;
    }
    if (stroke == right_alt_up) {
        stroke = application_up;
        return;
    }

    if (stroke == right_win_down) {
        stroke = right_alt_down;
        return;
    }
    if (stroke == right_win_up) {
        stroke = right_alt_up;
        return;
    }

    if (stroke == f13_down) {
        stroke = insert_down;
        return;
    }
    if (stroke == f13_up) {
        stroke = insert_up;
        return;
    }

    if (stroke == f14_down) {
        stroke = volume_down_down;
        return;
    }
    if (stroke == f14_up) {
        stroke = volume_down_up;
        return;
    }

    if (stroke == f15_down) {
        stroke = volume_up_down;
        return;
    }
    if (stroke == f15_up) {
        stroke = volume_up_up;
        return;
    }


}


int main()
{
    InterceptionContext context;
    InterceptionDevice device;
    InterceptionKeyStroke stroke;

//    raise_process_priority();

    context = interception_create_context();

//    interception_set_filter(context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP);
    interception_set_filter(context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_ALL);

    while (interception_receive(context, device = interception_wait(context), (InterceptionStroke *)&stroke, 1) > 0) {

        substitute(stroke);

//        std::cout << std::hex << stroke.state << "_" << stroke.code;

        interception_send(context, device, (InterceptionStroke *)&stroke, 1);

//        if (stroke.code == SCANCODE_ESC) break;
    }

    interception_destroy_context(context);

    return 0;
}
