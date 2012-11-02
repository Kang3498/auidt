package ${packageName};

import swssm.auidt.activity.AUIDTActivity;
import swssm.auidt.object.*;
import swssm.auidt.view.AUIDTView.LAYOUT;
import swssm.auidt.view.AUIDTView.OBJECT;
import swssm.auidt.view.AUIDTView.SYSTEMTEXTURE;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.support.v4.app.NavUtils;

public class ${activityClass} extends AUIDTActivity {

    AUIDTView mAUIDTView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
	mAUIDTView = new AUIDTView(getApplicationContext());
        setContentView(mAUIDTView);
        <#if parentActivityClass != "">
        getActionBar().setDisplayHomeAsUpEnabled(true);
        </#if>
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.${menuName}, menu);
        return true;
    }
    <#include "include_onOptionsItemSelected.java.ftl">
}
