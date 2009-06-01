// Keyboard_as.hx:  ActionScript 3 "Keyboard" class, for Gnash.
//
//
//   Copyright (C) 2009 Free Software Foundation, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

// This test case must be processed by CPP before compiling to include the
//  DejaGnu.hx header file for the testing framework support.

#if flash9
import flash.ui.Keyboard;
import flash.display.MovieClip;
#else
import flash.Key;
import flash.MovieClip;
#end
import flash.Lib;
import Type;

// import our testing API
import DejaGnu;

// Class must be named with the _as suffix, as that's the same name as the file.
class Keyboard_as {
	static function main(){
			#if flash9
			// Tests to see if all the properties exist. All these do is test for
			// existance of a property, and don't test the functionality at all. This
			// is primarily useful only to test completeness of the API implementation.
				if (Keyboard.capsLock == false || true) {
					DejaGnu.pass("Keyboard.capsLock property exists");
				} else {
					DejaGnu.fail("Keyboard.capsLock property doesn't exist");
				}
				if (Keyboard.numLock == false || true) {
					DejaGnu.pass("Keyboard.numLock property exists");
				} else {
					DejaGnu.fail("Keyboard.numLock property doesn't exist");
				}
	
			// Tests to see if all the methods exist. All these do is test for
			// existance of a method, and don't test the functionality at all. This
			// is primarily useful only to test completeness of the API implementation.
			if (Type.typeof(Keyboard.isAccessible) == ValueType.TFunction) {
				DejaGnu.pass("Keyboard::isAccessible() method exists");
			} else {
				DejaGnu.fail("Keyboard::isAccessible() method doesn't exist");
			}
			#end
			
			//check < flash9 methods
			#if !flash9
			//this appears that it should be supported, but is not currently
			//supported by haxe
			//if (Type.typeof(Key.isAccessible) == ValueType.TFunction){
			//	DejaGnu.pass("Key::isAccessible() method exists");
			//} else {
			//	DejaGnu.fail("Key::isAccessible() method doesn't exist");
			//}
			
			if (Type.typeof(Key.addListener) == ValueType.TFunction){
				DejaGnu.pass("Key::addListener() method exists");
			} else {
				DejaGnu.fail("Key::addListener() method doesn't exist");
			}
			
			if (Type.typeof(Key.getAscii) == ValueType.TFunction){
				DejaGnu.pass("Key::getAscii() method exists");
			} else {
				DejaGnu.fail("Key::getAscii() method doesn't exist");
			}
			
			if (Type.typeof(Key.getCode) == ValueType.TFunction){
				DejaGnu.pass("Key::getCode() method exists");
			} else {
				DejaGnu.fail("Key::getCode() method doesn't exist");
			}
			
			if (Type.typeof(Key.isDown) == ValueType.TFunction){
				DejaGnu.pass("Key::isDown() method exists");
			} else {
				DejaGnu.fail("Key::isDown() method doesn't exist");
			}
			
			if (Type.typeof(Key.isToggled) == ValueType.TFunction){
				DejaGnu.pass("Key::isToggled() method exists");
			} else {
				DejaGnu.fail("Key::isToggled() method doesn't exist");
			}
			
			if (Type.typeof(Key.removeListener) == ValueType.TFunction){
				DejaGnu.pass("Key::removeListener() method exists");
			} else {
				DejaGnu.fail("Key::removeListener() method doesn't exist");
			}
			
			#end
			
			//testing for AIR-only keystrokes
			#if !flash
				if (Keyboard.A == 65) {
					DejaGnu.pass("Keyboard::A() method exists");
				} else {
					DejaGnu.fail("Keyboard::A() method doesn't exist");
				}
				if (Keyboard.ALTERNATE == 18) {
					DejaGnu.pass("Keyboard::ALTERNATE() method exists");
				} else {
					DejaGnu.fail("Keyboard::ALTERNATE() method doesn't exist");
				}
				if (Keyboard.B == 66) {
					DejaGnu.pass("Keyboard::B() method exists");
				} else {
					DejaGnu.fail("Keyboard::B() method doesn't exist");
				}
				if (Keyboard.BACKQUOTE == 192) {
					DejaGnu.pass("Keyboard::BACKQUOTE() method exists");
				} else {
					DejaGnu.fail("Keyboard::BACKQUOTE() method doesn't exist");
				}
				if (Keyboard.BACKSLASH == 220) {
					DejaGnu.pass("Keyboard::BACKSLASH() method exists");
				} else {
					DejaGnu.fail("Keyboard::BACKSLASH() method doesn't exist");
				}
				if (Keyboard.C == 67) {
					DejaGnu.pass("Keyboard::C() method exists");
				} else {
					DejaGnu.fail("Keyboard::C() method doesn't exist");
				}
				if (Keyboard.CharCodeStrings == 0) {
					DejaGnu.pass("Keyboard::CharCodeStrings() method exists");
				} else {
					DejaGnu.fail("Keyboard::CharCodeStrings() method doesn't exist");
				}
				if (Keyboard.COMMA == 188) {
					DejaGnu.pass("Keyboard::COMMA() method exists");
				} else {
					DejaGnu.fail("Keyboard::COMMA() method doesn't exist");
				}
				if (Keyboard.COMMAND == 15) {
					DejaGnu.pass("Keyboard::COMMAND() method exists");
				} else {
					DejaGnu.fail("Keyboard::COMMAND() method doesn't exist");
				}
				if (Keyboard.D == 68) {
					DejaGnu.pass("Keyboard::D() method exists");
				} else {
					DejaGnu.fail("Keyboard::D() method doesn't exist");
				}
				if (Keyboard.E == 69) {
					DejaGnu.pass("Keyboard::E() method exists");
				} else {
					DejaGnu.fail("Keyboard::E() method doesn't exist");
				}
				if (Keyboard.EQUAL == 187) {
					DejaGnu.pass("Keyboard::EQUAL() method exists");
				} else {
					DejaGnu.fail("Keyboard::EQUAL() method doesn't exist");
				}
				if (Keyboard.F == 70) {
					DejaGnu.pass("Keyboard::F() method exists");
				} else {
					DejaGnu.fail("Keyboard::F() method doesn't exist");
				}
				if (Keyboard.G == 71) {
					DejaGnu.pass("Keyboard::G() method exists");
				} else {
					DejaGnu.fail("Keyboard::G() method doesn't exist");
				}
				if (Keyboard.H == 72) {
					DejaGnu.pass("Keyboard::H() method exists");
				} else {
					DejaGnu.fail("Keyboard::H() method doesn't exist");
				}
				if (Keyboard.I == 0) {
					DejaGnu.pass("Keyboard::I() method exists");
				} else {
					DejaGnu.fail("Keyboard::I() method doesn't exist");
				}
				if (Keyboard.J == 74) {
					DejaGnu.pass("Keyboard::J() method exists");
				} else {
					DejaGnu.fail("Keyboard::J() method doesn't exist");
				}
				if (Keyboard.K == 75) {
					DejaGnu.pass("Keyboard::K() method exists");
				} else {
					DejaGnu.fail("Keyboard::K() method doesn't exist");
				}
				if (Keyboard.BEGIN) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.BREAK) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.CLEARDISPLAY) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.CLEARLINE) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.DELETE) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.DELETECHAR) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.DELETELINE) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.DOWNARROW) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.END) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.EXECUTE) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F1) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F10) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F11) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F12) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F13) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F14) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F15) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F16) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F17) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F18) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F19) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F2) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F20) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F21) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F22) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F23) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F24) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F25) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F26) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F27) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F28) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F29) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F3) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F30) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F31) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F32) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F33) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F34) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F35) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F4) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F5) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F6) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F7) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F8) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.F9) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.FIND) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.HELP) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.HOME) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.INSERT) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.INSERTCHAR) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.INSERTLINE) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.LEFTARROW) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.MENU) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.MODESWITCH) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.NEXT) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.PAGEDOWN) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.PAGEUP) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.PAUSE) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.PREV) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.PRINT) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.PRINTSCREEN) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.REDO) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.RESET) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.RIGHTARROW) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.SCROLLLOCK) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.SELECT) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.STOP) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.SYSREQ) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.SYSTEM) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.UNDO) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.UPARROW) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.USER) {
					DejaGnu.pass("Keyboard::KEYNAME() method exists");
				} else {
					DejaGnu.fail("Keyboard::KEYNAME() method doesn't exist");
				}
				if (Keyboard.L == 0) {
					DejaGnu.pass("Keyboard::L() method exists");
				} else {
					DejaGnu.fail("Keyboard::L() method doesn't exist");
				}
				if (Keyboard.LEFT == 0) {
					DejaGnu.pass("Keyboard::LEFT() method exists");
				} else {
					DejaGnu.fail("Keyboard::LEFT() method doesn't exist");
				}
				if (Keyboard.LEFTBRACKET == 0) {
					DejaGnu.pass("Keyboard::LEFTBRACKET() method exists");
				} else {
					DejaGnu.fail("Keyboard::LEFTBRACKET() method doesn't exist");
				}
				if (Keyboard.M == 0) {
					DejaGnu.pass("Keyboard::M() method exists");
				} else {
					DejaGnu.fail("Keyboard::M() method doesn't exist");
				}
				if (Keyboard.MINUS == 0) {
					DejaGnu.pass("Keyboard::MINUS() method exists");
				} else {
					DejaGnu.fail("Keyboard::MINUS() method doesn't exist");
				}
				if (Keyboard.N == 0) {
					DejaGnu.pass("Keyboard::N() method exists");
				} else {
					DejaGnu.fail("Keyboard::N() method doesn't exist");
				}
				if (Keyboard.NUMBER == 0) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMBER == 1) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMBER == 2) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMBER == 3) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMBER == 4) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMBER == 5) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMBER == 6) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMBER == 7) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMBER == 8) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMBER == 9) {
					DejaGnu.pass("Keyboard::NUMBER() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMBER() method doesn't exist");
				}
				if (Keyboard.NUMPAD == 0) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.O == 0) {
					DejaGnu.pass("Keyboard::O() method exists");
				} else {
					DejaGnu.fail("Keyboard::O() method doesn't exist");
				}
				if (Keyboard.P == 0) {
					DejaGnu.pass("Keyboard::P() method exists");
				} else {
					DejaGnu.fail("Keyboard::P() method doesn't exist");
				}
				if (Keyboard.PERIOD == 0) {
					DejaGnu.pass("Keyboard::PERIOD() method exists");
				} else {
					DejaGnu.fail("Keyboard::PERIOD() method doesn't exist");
				}
				if (Keyboard.Q == 0) {
					DejaGnu.pass("Keyboard::Q() method exists");
				} else {
					DejaGnu.fail("Keyboard::Q() method doesn't exist");
				}
				if (Keyboard.QUOTE == 0) {
					DejaGnu.pass("Keyboard::QUOTE() method exists");
				} else {
					DejaGnu.fail("Keyboard::QUOTE() method doesn't exist");
				}
				if (Keyboard.R == 0) {
					DejaGnu.pass("Keyboard::R() method exists");
				} else {
					DejaGnu.fail("Keyboard::R() method doesn't exist");
				}
				if (Keyboard.RIGHTBRACKET == 0) {
					DejaGnu.pass("Keyboard::RIGHTBRACKET() method exists");
				} else {
					DejaGnu.fail("Keyboard::RIGHTBRACKET() method doesn't exist");
				}
				if (Keyboard.S == 0) {
					DejaGnu.pass("Keyboard::S() method exists");
				} else {
					DejaGnu.fail("Keyboard::S() method doesn't exist");
				}
				if (Keyboard.SEMICOLON == 0) {
					DejaGnu.pass("Keyboard::SEMICOLON() method exists");
				} else {
					DejaGnu.fail("Keyboard::SEMICOLON() method doesn't exist");
				}
				if (Keyboard.SLASH == 191) {
					DejaGnu.pass("Keyboard::SLASH() method exists");
				} else {
					DejaGnu.fail("Keyboard::SLASH() method doesn't exist");
				}
				if (Keyboard.STRING_BEGIN) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_BREAK) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_CLEARDISPLAY) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_CLEARLINE) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_DELETE) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_DELETECHAR) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_DELETELINE) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_DOWNARROW) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_END) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_EXECUTE) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F1) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F10) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F11) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F12) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F13) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F14) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F15) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F16) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F17) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F18) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F19) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F2) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F20) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F21) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F22) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F23) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F24) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F25) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F26) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F27) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F28) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F29) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F3) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F30) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F31) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F32) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F33) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F34) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F35) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F4) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F5) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F6) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F7) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F8) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_F9) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_FIND) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_HELP) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_HOME) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_INSERT) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_INSERTCHAR) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_INSERTLINE) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_LEFTARROW) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_MENU) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_MODESWITCH) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_NEXT) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_PAGEDOWN) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_PAGEUP) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_PAUSE) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_PREV) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_PRINT) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_PRINTSCREEN) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_REDO) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_RESET) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_RIGHTARROW) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_SCROLLLOCK) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_SELECT) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_STOP) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.STRING_SYSREQ) {
					DejaGnu.pass("Keyboard::STRING() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.SYSTEM) {
					DejaGnu.pass("Keyboard::SYSTEM() method exists");
				} else {
					DejaGnu.fail("Keyboard::STRING() method doesn't exist");
				}
				if (Keyboard.UNDO) {
					DejaGnu.pass("Keyboard::UNDO() method exists");
				} else {
					DejaGnu.fail("Keyboard::UNDO() method doesn't exist");
				}
				if (Keyboard.UPARROW) {
					DejaGnu.pass("Keyboard::UPARROW() method exists");
				} else {
					DejaGnu.fail("Keyboard::(UPARROW) method doesn't exist");
				}
				if (Keyboard.USER) {
					DejaGnu.pass("Keyboard::USER() method exists");
				} else {
					DejaGnu.fail("Keyboard::USER() method doesn't exist");
				}
				if (Keyboard.T == 0) {
					DejaGnu.pass("Keyboard::T() method exists");
				} else {
					DejaGnu.fail("Keyboard::T() method doesn't exist");
				}
				 if (Keyboard.U == 0) {
					DejaGnu.pass("Keyboard::U() method exists");
				} else {
					DejaGnu.fail("Keyboard::U() method doesn't exist");
				}
				if (Keyboard.V == 0) {
					DejaGnu.pass("Keyboard::V() method exists");
				} else {
					DejaGnu.fail("Keyboard::V() method doesn't exist");
				}
				if (Keyboard.W == 0) {
					DejaGnu.pass("Keyboard::W() method exists");
				} else {
					DejaGnu.fail("Keyboard::W() method doesn't exist");
				}
				if (Keyboard.X == 0) {
					DejaGnu.pass("Keyboard::X() method exists");
				} else {
					DejaGnu.fail("Keyboard::X() method doesn't exist");
				}
				if (Keyboard.Y == 0) {
					DejaGnu.pass("Keyboard::Y() method exists");
				} else {
					DejaGnu.fail("Keyboard::Y() method doesn't exist");
				}
				if (Keyboard.Z == 0) {
					DejaGnu.pass("Keyboard::Z() method exists");
				} else {
					DejaGnu.fail("Keyboard::Z() method doesn't exist");
				}
		#end
		#if (flash9 || !flash)
				if (Keyboard.BACKSPACE == 8) {
					DejaGnu.pass("Keyboard::BACKSPACE() method exists");
				} else {
					DejaGnu.fail("Keyboard::BACKSPACE() method doesn't exist");
				}
				if (Keyboard.CAPS_LOCK == 20) {
					DejaGnu.pass("Keyboard::CAPS() method exists");
				} else {
					DejaGnu.fail("Keyboard::CAPS() method doesn't exist");
				}
				if (Keyboard.CONTROL == 17) {
					DejaGnu.pass("Keyboard::CONTROL() method exists");
				} else {
					DejaGnu.fail("Keyboard::CONTROL() method doesn't exist");
				}
				if (Keyboard.DELETE == 46) {
					DejaGnu.pass("Keyboard::DELETE() method exists");
				} else {
					DejaGnu.fail("Keyboard::DELETE() method doesn't exist");
				}
				if (Keyboard.DOWN == 40) {
					DejaGnu.pass("Keyboard::DOWN() method exists");
				} else {
					DejaGnu.fail("Keyboard::DOWN() method doesn't exist");
				}
				if (Keyboard.END == 35) {
					DejaGnu.pass("Keyboard::END() method exists");
				} else {
					DejaGnu.fail("Keyboard::END() method doesn't exist");
				}
				if (Keyboard.ENTER == 13) {
					DejaGnu.pass("Keyboard::ENTER() method exists");
				} else {
					DejaGnu.fail("Keyboard::ENTER() method doesn't exist");
				}
				if (Keyboard.ESCAPE == 27) {
					DejaGnu.pass("Keyboard::ESCAPE() method exists");
				} else {
					DejaGnu.fail("Keyboard::ESCAPE() method doesn't exist");
				}
				if (Keyboard.F1 == 112) {
					DejaGnu.pass("Keyboard::F1() method exists");
				} else {
					DejaGnu.fail("Keyboard::F1() method doesn't exist");
				}
				if (Keyboard.F10 == 121) {
					DejaGnu.pass("Keyboard::F10() method exists");
				} else {
					DejaGnu.fail("Keyboard::F10() method doesn't exist");
				}
				if (Keyboard.F11 == 122) {
					DejaGnu.pass("Keyboard::F11() method exists");
				} else {
					DejaGnu.fail("Keyboard::F11() method doesn't exist");
				}
				if (Keyboard.F12 == 123) {
					DejaGnu.pass("Keyboard::F12() method exists");
				} else {
					DejaGnu.fail("Keyboard::F12() method doesn't exist");
				}
				if (Keyboard.F13 == 124) {
					DejaGnu.pass("Keyboard::F13() method exists");
				} else {
					DejaGnu.fail("Keyboard::F13() method doesn't exist");
				}
				if (Keyboard.F14 == 125) {
					DejaGnu.pass("Keyboard::F14() method exists");
				} else {
					DejaGnu.fail("Keyboard::F14() method doesn't exist");
				}
				if (Keyboard.F15 == 126) {
					DejaGnu.pass("Keyboard::F15() method exists");
				} else {
					DejaGnu.fail("Keyboard::F15() method doesn't exist");
				}
				if (Keyboard.F2 == 113) {
					DejaGnu.pass("Keyboard::F2() method exists");
				} else {
					DejaGnu.fail("Keyboard::F2() method doesn't exist");
				}
				if (Keyboard.F3 == 114) {
					DejaGnu.pass("Keyboard::F3() method exists");
				} else {
					DejaGnu.fail("Keyboard::F3() method doesn't exist");
				}
				if (Keyboard.F4 == 115) {
					DejaGnu.pass("Keyboard::F4() method exists");
				} else {
					DejaGnu.fail("Keyboard::F4() method doesn't exist");
				}
				if (Keyboard.F5 == 116) {
					DejaGnu.pass("Keyboard::F5() method exists");
				} else {
					DejaGnu.fail("Keyboard::F5() method doesn't exist");
				}
				if (Keyboard.F6 == 117) {
					DejaGnu.pass("Keyboard::F6() method exists");
				} else {
					DejaGnu.fail("Keyboard::F6() method doesn't exist");
				}
				if (Keyboard.F7 == 118) {
					DejaGnu.pass("Keyboard::F7() method exists");
				} else {
					DejaGnu.fail("Keyboard::F7() method doesn't exist");
				}
				if (Keyboard.F8 == 119) {
					DejaGnu.pass("Keyboard::F8() method exists");
				} else {
					DejaGnu.fail("Keyboard::F8() method doesn't exist");
				}
				if (Keyboard.F9 == 120) {
					DejaGnu.pass("Keyboard::F9() method exists");
				} else {
					DejaGnu.fail("Keyboard::F9() method doesn't exist");
				}
				if (Keyboard.HOME == 36) {
					DejaGnu.pass("Keyboard::HOME() method exists");
				} else {
					DejaGnu.fail("Keyboard::HOME() method doesn't exist");
				}
				if (Keyboard.INSERT == 45) {
					DejaGnu.pass("Keyboard::INSERT() method exists");
				} else {
					DejaGnu.fail("Keyboard::INSERT() method doesn't exist");
				}
				if (Keyboard.NUMPAD_0 == 96) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_1 == 97) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_2 == 98) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_3 == 99) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_4 == 100) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_5 == 101) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_6 == 102) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_7 == 103) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_8 == 104) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_9 == 105) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_ADD == 107) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_DECIMAL == 110) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_DIVIDE == 109) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_ENTER == 108) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_MULTIPLY == 106) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.NUMPAD_SUBTRACT == 109) {
					DejaGnu.pass("Keyboard::NUMPAD() method exists");
				} else {
					DejaGnu.fail("Keyboard::NUMPAD() method doesn't exist");
				}
				if (Keyboard.PAGE_DOWN == 34) {
					DejaGnu.pass("Keyboard::PAGE() method exists");
				} else {
					DejaGnu.fail("Keyboard::PAGE() method doesn't exist");
				}
				if (Keyboard.PAGE_UP == 33) {
					DejaGnu.pass("Keyboard::PAGE() method exists");
				} else {
					DejaGnu.fail("Keyboard::PAGE() method doesn't exist");
				}
				if (Keyboard.RIGHT == 39) {
					DejaGnu.pass("Keyboard::RIGHT() method exists");
				} else {
					DejaGnu.fail("Keyboard::RIGHT() method doesn't exist");
				}
				if (Keyboard.SHIFT == 16) {
					DejaGnu.pass("Keyboard::SHIFT() method exists");
				} else {
					DejaGnu.fail("Keyboard::SHIFT() method doesn't exist");
				}
				if (Keyboard.SPACE == 32) {
					DejaGnu.pass("Keyboard::SPACE() method exists");
				} else {
					DejaGnu.fail("Keyboard::SPACE() method doesn't exist");
				}
				if (Keyboard.TAB == 9) {
					DejaGnu.pass("Keyboard::TAB() method exists");
				} else {
					DejaGnu.fail("Keyboard::TAB() method doesn't exist");
				}
				if (Keyboard.UP == 38) {
					DejaGnu.pass("Keyboard::UP() method exists");
				} else {
					DejaGnu.fail("Keyboard::UP() method doesn't exist");
				}
		#end
		//checking old classes
		#if (!flash9 && !!flash)
				if (Key.BACKSPACE == 8) {
					DejaGnu.pass("Key::BACKSPACE() method exists");
				} else {
					DejaGnu.fail("Key::BACKSPACE() method doesn't exist");
				}
				if (Key.CAPSLOCK == 20) {
					DejaGnu.pass("Key::CAPS() method exists");
				} else {
					DejaGnu.fail("Key::CAPS() method doesn't exist");
				}
				if (Key.CONTROL == 17) {
					DejaGnu.pass("Key::CONTROL() method exists");
				} else {
					DejaGnu.fail("Key::CONTROL() method doesn't exist");
				}
				if (Key.DELETEKEY == 46) {
					DejaGnu.pass("Key::DELETE() method exists");
				} else {
					DejaGnu.fail("Key::DELETE() method doesn't exist");
				}
				if (Key.DOWN == 40) {
					DejaGnu.pass("Key::DOWN() method exists");
				} else {
					DejaGnu.fail("Key::DOWN() method doesn't exist");
				}
				if (Key.END == 35) {
					DejaGnu.pass("Key::END() method exists");
				} else {
					DejaGnu.fail("Key::END() method doesn't exist");
				}
				if (Key.ENTER == 13) {
					DejaGnu.pass("Key::ENTER() method exists");
				} else {
					DejaGnu.fail("Key::ENTER() method doesn't exist");
				}
				if (Key.ESCAPE == 27) {
					DejaGnu.pass("Key::ESCAPE() method exists");
				} else {
					DejaGnu.fail("Key::ESCAPE() method doesn't exist");
				}
				if (Key.HOME == 36) {
					DejaGnu.pass("Key::HOME() method exists");
				} else {
					DejaGnu.fail("Key::HOME() method doesn't exist");
				}
				if (Key.INSERT == 45) {
					DejaGnu.pass("Key::INSERT() method exists");
				} else {
					DejaGnu.fail("Key::INSERT() method doesn't exist");
				}
				if (Key.RIGHT == 39) {
					DejaGnu.pass("Key::RIGHT() method exists");
				} else {
					DejaGnu.fail("Key::RIGHT() method doesn't exist");
				}
				if (Key.SHIFT == 16) {
					DejaGnu.pass("Key::SHIFT() method exists");
				} else {
					DejaGnu.fail("Key::SHIFT() method doesn't exist");
				}
				if (Key.SPACE == 32) {
					DejaGnu.pass("Key::SPACE() method exists");
				} else {
					DejaGnu.fail("Key::SPACE() method doesn't exist");
				}
				if (Key.TAB == 9) {
					DejaGnu.pass("Key::TAB() method exists");
				} else {
					DejaGnu.fail("Key::TAB() method doesn't exist");
				}
				if (Key.UP == 38) {
					DejaGnu.pass("Key::UP() method exists");
				} else {
					DejaGnu.fail("Key::UP() method doesn't exist");
				}
			#end
			
			// Call this after finishing all tests. It prints out the totals.
			DejaGnu.done();
			
		}
}