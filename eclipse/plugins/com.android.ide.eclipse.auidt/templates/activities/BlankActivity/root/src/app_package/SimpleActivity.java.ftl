package ${packageName};

import swssm.auidt.activity.AUIDTActivity;
import android.os.Bundle;
import android.view.Menu;

public class ${activityClass} extends AUIDTActivity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        
        super.onCreate(savedInstanceState);
        setContentView(R.layout.${layoutName});

		 // your code

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
