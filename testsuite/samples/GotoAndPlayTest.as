// gotoAndPlay() testcase
// Source file provided for reference

// This code is in frame #2 of a 3-frame file!

var temp = _currentframe;

if (temp!=2) {
 
  trace("UNRESOLVED: _currentframe reports frame "+temp+", can't continue test");
  
} else {

  trace("PASSED: _currentframe reports frame 2");
  
  gotoAndPlay(temp);
  
  if (_currentframe==temp) 
    trace("PASSED: _currentframe is correct after gotoAndPlay() call");
  else
    trace("FAILED: _currentframe reports frame "+_currentframe+" instead of "+temp);
  
}

stop();
