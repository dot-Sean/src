package com.ayutaya;
import java.io.Serializable;
public class Polygon implements Serializable {
    private static final long serialVersionUID = 1L;
    private double rRadius = 0;
    private double rArea = 0;
    private int nNumVertex = 0;
    public Polygon() {}
    public double getRadius () {
        return (rRadius);
    }
    public double getArea () {
        if (nNumVertex > 0) {
             rArea = nNumVertex * rRadius * rRadius * 
              Math.sin(Math.PI / nNumVertex) *
              Math.cos(Math.PI / nNumVertex);
        } else {
             rArea = 0;
        }
        return (rArea);
    }
    public int getNumVertex () {
        return (nNumVertex);
    }
    public void setRadius(double r) {
        rRadius = r;
    }
    public void setNumVertex(int n) {
        nNumVertex = n;
    }
    public long sumIntAngle () {
        return (180 * nNumVertex - 360);
    }
}
