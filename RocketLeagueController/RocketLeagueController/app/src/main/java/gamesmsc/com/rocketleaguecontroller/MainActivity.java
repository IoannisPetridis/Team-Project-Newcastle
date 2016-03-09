package gamesmsc.com.rocketleaguecontroller;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.provider.Settings;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends AppCompatActivity {

    private DialogFragment dialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    public boolean checkConnection(Context context) {
        //Get Connectivity Manager
        ConnectivityManager cm = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetwork = cm.getActiveNetworkInfo();
        boolean isConnected = activeNetwork != null && activeNetwork.isConnectedOrConnecting();
        if (!isConnected) {
            AlertDialog.Builder builder = new AlertDialog.Builder(this);
            builder.setTitle("Wi-Fi or data is not enabled");
            builder.setMessage("Please enable Wi-Fi/data usage");
            builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialogInterface, int i) {
                    // Show mobile data settings when the user presses OK
                    Intent intent = new Intent(Settings.ACTION_DATA_ROAMING_SETTINGS);
                    startActivity(intent);
                }
            });
            Dialog alertDialog = builder.create();
            alertDialog.setCanceledOnTouchOutside(false);
            alertDialog.show();

        }
        return isConnected;
    }

    public void buttonOnClickInfo(View v) {
        dialog = new CreateDialog();
        dialog.show(getFragmentManager(),"info");
        //Intent intent = new Intent(this, RegisterActivity.class);
       // startActivity(intent);
    }

    public void buttonOnClickPlay(View v) {
        if (checkConnection(getApplicationContext())) {
            Intent intent = new Intent(this, PlayActivity.class);
            startActivity(intent);
        }
    }
}
