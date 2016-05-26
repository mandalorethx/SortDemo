package com.example.matt.sortdemo;

/**
 * Created by matt on 5/25/16.
 */
public class SortDemoRenderer {
    static {
        System.loadLibrary("SortDemoRenderer");
    }

    public static native void create_renderer(int width, int height);
    public static native void destroy_renderer();
    public static native void draw_frame();
    public static native void add_mesh(String pszFile);
}
