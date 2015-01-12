package it.unibz.enactmobile;

import java.util.ArrayList;

import android.graphics.Bitmap;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentStatePagerAdapter;
import android.view.ViewGroup;


public class FragmentPagerAdapter extends FragmentStatePagerAdapter {
	 
    private ArrayList<String> imagesList;
    private String inputPath;
 
    public FragmentPagerAdapter(FragmentManager fm, ArrayList<String> imagesList) {
    //public FragmentPagerAdapter(FragmentManager fm, String path) {
        super(fm);
        this.imagesList = imagesList;
    }
    
    @Override
    public int getCount() {
        return imagesList.size();
    	//return 666;
    }
    
    @Override
    public void destroyItem(ViewGroup container, int position, Object object) {
        super.destroyItem(container, position, object);
    }
    
    @Override
    public Fragment getItem(int position) {
        FragmentImageView f = FragmentImageView.newInstance();
        //f.setImageList(imagesList.get(position));
        //f.setImageList(inputPath);
        f.setImageList(imagesList.get(position));
        return f;
    }
    
    public void setNewList(ArrayList<String> list){
    	this.imagesList = list;
    }
}
//- See more at: http://www.theappguruz.com/blog/android-image-fragment-pager-view/#sthash.2QCoGC9v.dpuf