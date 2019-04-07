
class MyTextPiroPiro {
	string text;
	float timeToRender;
	float timeBegan;
	bool  timeSet, done;
    float tick;
    float timeStamp;
    
    
public:
	
	void init() {
		text = "";
		timeToRender = 0;
        timeBegan = 0;
		timeSet = done = false;
        timeStamp = ofGetElapsedTimef();
	}
	
	MyTextPiroPiro() {
		init();
	}
	
	MyTextPiroPiro(string _text, float _timeToRender = 5) {
		text = _text;
		timeToRender= _timeToRender;
		done = false;
	}
    
    void update(){
       
    }
	
	string whatToRender() {
		if(!done) {
             tick = ofGetElapsedTimef() - timeStamp;
			if(!timeSet) {
                timeBegan = tick;
				timeSet = true;
			} 
			
			int n = (int)((tick / (timeSet+timeToRender)) * text.length());
			
			if (n + 1 == (int)text.length() ) done = true;
			
			return text.substr(0, min( n, (int)text.length()) ); 
		} else {
    		return text;
		}
	}
	 
	void resetTime() {
		timeSet = false;
	}
	
	void setTimeToRender(float _timeToRender) {
		resetTime();
		timeToRender = _timeToRender;
		done = false;
	}
	
	void setTextToRender(string _text) {
		text = _text;
	}
	
	bool isDone() {
		return done;
	}
};