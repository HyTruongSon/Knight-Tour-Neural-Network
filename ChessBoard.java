// Software: Knight's Tour - Visualization
// Author: Hy Truong Son
// Major: BSc. Computer Science
// Class: 2013 - 2016
// Institution: Eotvos Lorand University
// Email: sonpascal93@gmail.com
// Website: http://people.inf.elte.hu/hytruongson/
// Copyright 2015 (c) Hy Truong Son. All rights reserved.

import java.io.*;
import java.awt.*;
import javax.swing.*;

import java.util.Arrays;
import java.util.Iterator;
import java.util.Scanner;

import java.awt.geom.Ellipse2D;

import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import javax.imageio.ImageWriter;
import javax.imageio.stream.ImageOutputStream;

public class ChessBoard {
	
	static String Solution_File = "Solution.txt";
	static String Solution_Image = "Solution.png";
	
	static int Cell_Length = 50;
	static int Big_Diameter = 20;
	static int Small_Diameter = 10;
	
	static int width, height;
	static int n;
	static int label[][];
	
	static class aPoint {
		public int x, y;
	}
	static aPoint Point[];
	
	public static String GetType(String FileName){
		int i, j;
		String res;
		j = 0;
		for (i = 0; i < FileName.length(); i++)
			if (FileName.charAt(i) == '.'){
				j = i;
				break;
			}
		res = "";
		for (i = j + 1; i < FileName.length(); i++) res += FileName.charAt(i);
		return res;
	}
	
	public static void DrawLine(BufferedImage image, int x1, int y1, int x2, int y2){
		Graphics2D g2d = image.createGraphics();
		g2d.setColor(Color.RED);
		
		x1 = x1 * Cell_Length + Cell_Length / 2;
		y1 = y1 * Cell_Length + Cell_Length / 2;
		x2 = x2 * Cell_Length + Cell_Length / 2;
		y2 = y2 * Cell_Length + Cell_Length / 2;
		g2d.drawLine(x1, y1, x2, y2);
	}
	
	public static void DrawRect(BufferedImage image, int x1, int y1, int x2, int y2){
		Graphics2D g2d = image.createGraphics();
		g2d.setColor(Color.WHITE);
		g2d.fillRect(x1, y1, x2 - x1 + 1, y2 - y1 + 1);
	}
	
	public static void DrawCircle(BufferedImage image, int x, int y, int r, String color){
		Graphics2D g2d = image.createGraphics();
		
		if (color.equals("GREEN"))
			g2d.setColor(Color.GREEN);
		
		if (color.equals("YELLOW"))
			g2d.setColor(Color.YELLOW);
		
		if (color.equals("RED"))
			g2d.setColor(Color.RED);
		
		x = x * Cell_Length + Cell_Length / 2 - r / 2;
		y = y * Cell_Length + Cell_Length / 2 - r / 2;
		Ellipse2D.Double circle = new Ellipse2D.Double(x, y, r, r);
		g2d.fill(circle);
	}
	
	public static void Input() throws IOException {
		Scanner input = new Scanner(new File(Solution_File));
		
		n = input.nextInt();
		
		label = new int [n][n];
		Point = new aPoint [n * n];
		
		for (int i = 0; i < n * n; i++)
			Point[i] = new aPoint();
			
		for (int j = 0; j < n; j++)
			for (int i = 0; i < n; i++){
				label[i][j] = input.nextInt();
				Point[label[i][j] - 1].x = i;
				Point[label[i][j] - 1].y = j;
			}
			
		input.close();
	}
	
	public static void Visualization() throws IOException {
		width = Cell_Length * n;
		height = Cell_Length * n;
		BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++){
				int color = ((i % 2) + (j % 2)) % 2;
				if (color == 0)
					DrawRect(image, i * Cell_Length, j * Cell_Length, (i + 1) * Cell_Length - 1, (j + 1) * Cell_Length - 1);
			}
			
		int sx = Point[0].x;
		int sy = Point[0].y;
		int fx = Point[n * n - 1].x;
		int fy = Point[n * n - 1].y;
		
		for (int i = 1; i < n * n; i++)
			DrawLine(image, Point[i].x, Point[i].y, Point[i - 1].x, Point[i - 1].y);
		
		if (Math.abs(fx - sx) * Math.abs(fy - sy) == 2){
			DrawLine(image, sx, sy, fx, fy);
			DrawCircle(image, sx, sy, Big_Diameter, "YELLOW"); 
			DrawCircle(image, fx, fy, Small_Diameter, "RED"); 
		}else{
			DrawCircle(image, sx, sy, Big_Diameter, "GREEN"); 
			DrawCircle(image, fx, fy, Big_Diameter, "GREEN"); 
		}
			
		for (int i = 1; i < n * n - 1; i++)
			DrawCircle(image, Point[i].x, Point[i].y, Small_Diameter, "RED"); 
		
		File file = new File(Solution_Image);
		ImageIO.write(image, GetType(Solution_Image), file);
	}
	
	public static void main(String args[]) throws IOException {
		Input();
		Visualization();
	}	
	
}
