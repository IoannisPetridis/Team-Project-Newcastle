package gamesmsc.com.rocketleaguecontroller;

import android.app.AlertDialog;
import android.app.Dialog;
import android.app.DialogFragment;
import android.os.Bundle;

public class CreateDialog extends DialogFragment {
    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState) {
        // Use the Builder class for convenient dialog construction
        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());
        builder.setMessage(R.string.info_text);
        builder.setTitle("Info");
        builder.setCancelable(true);
        // Create the AlertDialog object and return it
        return builder.create();
    }
}