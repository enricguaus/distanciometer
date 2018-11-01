(
p = SerialPort(
    "/dev/tty.usbserial-A9007Vvy",    //edit to match your port. SerialPort.listDevices
    baudrate: 57600,    //check that baudrate is the same as in arduino sketch
    crtscts: true);
)

//read 10bit serial data sent from Arduino's Serial.println
(
var s1,s2,s3,s4;
var data=[0,0,0,0];

w  = Window.new("Sheepdog", Rect(200, 400, 380, 390));
//w.onClose_({r.stop; x.free; b.free; c.free; d.free; e.free; c2.close});
s1 = LevelIndicator.new(w, Rect(10, 10, 60, 280));
s1.warning_(1.0);
s1.critical_(1.0);
s1.numTicks_(21);
s1.numMajorTicks_(5);

s2 = LevelIndicator.new(w, Rect(90, 10, 60, 280));
s2.warning_(1.0);
s2.critical_(1.0);
s2.numTicks_(21);
s2.numMajorTicks_(5);

s3 = LevelIndicator.new(w, Rect(170, 10, 60, 280));
s3.warning_(1.0);
s3.critical_(1.0);
s3.numTicks_(21);
s3.numMajorTicks_(5);

s4 = LevelIndicator.new(w, Rect(250, 10, 60, 280));
s4.warning_(1.0);
s4.critical_(1.0);
s4.numTicks_(21);
s4.numMajorTicks_(5);

w.front;

r= Routine({
    var byte, str, res;
    inf.do{|i|
        if(p.read==10, {
            str = "";
            while({byte = p.read; byte !=13 }, {
                str= str++byte.asAscii;
            });
			res=str.split($ );
			res.postln;
			data[0]=res[0].asInteger/700;
			data[1]=res[1].asInteger/700;
			data[2]=res[2].asInteger/700;
			data[3]=res[3].asInteger/700;
        });
    };
}).play;


t = {
  inf.do{
	{s1.value=data[0];s2.value=data[1];s3.value=data[2];s4.value=data[3]}.defer;
    0.4.wait; // 0.04 - 25 frames per second
  };
}.fork;
)


(
r.stop;
t.stop;
p.close;
w.close;
)

