package com.ayutaya.custom;
import javax.servlet.jsp.*;
import javax.servlet.jsp.tagext.*;
import java.io.*;
public class circle extends TagSupport{

	private static final long serialVersionUID = 1L;
	private double r=0;
	//パラメータ半径の取得
	public void setR(double r){this.r=r;}
	//タグの開始時に実行されるメソッド
	public int doStartTag() throws JspException	{
		double s=Math.PI*r*r;
		try	{
			pageContext.getOut().write(""+s);
		} catch(IOException e) {
			throw new JspException(e.getMessage());
		}
		return SKIP_BODY;
	}
}