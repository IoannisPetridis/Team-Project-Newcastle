package gamesmsc.com.rocketleaguecontroller;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class PlayActivity extends Activity {
    private TextView textView,textView2;
    int x,y;
    String selection;

    private String serverIpAddress = "10.66.67.185";

    private boolean connected = false;

    private Handler handler = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play);

        Spinner dropdown = (Spinner)findViewById(R.id.spinner);
        String[] items = new String[]{"No Powerup","Boost", "Weapon", "Invisibility"};
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_dropdown_item, items);
        dropdown.setAdapter(adapter);
    }

    public class ClientThread implements Runnable {
       // ObjectInputStream in;
        PrintWriter out;
        BufferedReader in;
        Socket socket;


        Spinner mySpinner=(Spinner) findViewById(R.id.spinner);
        String powerup = mySpinner.getSelectedItem().toString();
        public void run() {
            try {
                InetAddress serverAddr = InetAddress.getByName(serverIpAddress);
                Log.d("PlayActivity", "C: Connecting...");
                socket = new Socket(serverAddr, 4376);
                connected = true;
                while (connected) {
                    try { //WIFI is working, data is not but we don't need that anyway :P
                        Log.d("PlayActivity", "C: Sending command.");
                        out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
                        // WHERE YOU ISSUE THE COMMANDS
                        if (powerup !="No Powerup") {
                            selection = null;
                        }
                        if (selection !="w" && selection !="e") {
                            if (powerup !="No Powerup") {
                                out.println("2" + "*" + powerup + "*" + String.valueOf(x) + "*" + String.valueOf(y));
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            out.println("2"+"*"+selection+"*"+String.valueOf(x)+"*"+String.valueOf(y));
                        }
                        in = new BufferedReader(new InputStreamReader(socket.getInputStream()), 1);
                       // in = new ObjectInputStream(socket.getInputStream());
                        String message = (String) in.readLine(); //Server response...WORKS !
                        textView2 = (TextView)findViewById(R.id.textView2);
                        String finalmessage = "Message from Server:" + message; //This is the message from the server, we can only write it to the log for .. reasons
                        //textView2.setText(finalmessage);
                        //Log.d("PlayActivity", "Server message: "+message);
                        Log.d("PlayActivity", "Server message:" +message);
                        //System.out.println("Message from Server:"+ message);
                        Log.d("PlayActivity", "C: Sent.");
                    } catch (Exception e) {
                        Log.e("PlayActivity", "S: Error", e);
                    }
                    connected = false;
                }
                socket.close();
                Log.d("PlayActivity", "C: Closed.");
            } catch (Exception e) {
                Log.e("PlayActivity", "C: Error", e);
                connected = false;
            }
        }
    }

    public void buttonOnClickWeather(View v) {
        Spinner dropdown = (Spinner)findViewById(R.id.spinner);
        dropdown.setSelection(0);
        selection = "w";
    }

    public void buttonOnClickExplosion(View v) {
        Spinner dropdown = (Spinner)findViewById(R.id.spinner);
        dropdown.setSelection(0);
        selection = "e";

    }

    public void buttonOnClickPowerup(View v) {
        selection = "p";
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        x = (int)event.getX();
        y = (int)event.getY();
        textView = (TextView)findViewById(R.id.textView);
        textView.setText("Touched at (x,y) : ("+String.valueOf(x)+","+String.valueOf(y)+")");
        Thread cThread = new Thread(new PlayActivity.ClientThread());
        cThread.start();
        switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_MOVE:
            case MotionEvent.ACTION_UP:
        }
        return false;
    }
}
