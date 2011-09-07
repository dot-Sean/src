// http://www.itmedia.co.jp/enterprise/articles/0908/22/news001_3.html

import java.util.*;

//import System;
//import  System.Collections;
//import System.Collections.Generic;
//import System.Text;

//import java.lang.*;

public class BinaryFlips {
    public int minimalMoves(int A, int B, int K) {
        if (A == 0) {
            return (0);
        }
        if (A + B < K) {
            return (-1);
        }
        int[] results = new int[A + B + 1];
        for (int i = 0; i < results.length; i ++) {
            results[i] = -1;
        }
        List<Integer> currentNodes = new ArrayList<Integer>();
        currentNodes.add(A);
        List<Integer> openNodes = new ArrayList<Integer>();
        results[A] = 0;
        while (currentNodes.size() > 0) {
            for (int i: currentNodes) {
                for (
                 int turned0 = Math.max(0, K - (A + B - i));
                 turned0 <= Math.min(i, K);
                 turned0 ++ ) {
                    int nextZeros = i + (K - 2 * turned0);
                    if (results[nextZeros] == -1) {
                        if (nextZeros == 0) {
                            return (results[i] + 1);
                        }
                        results[nextZeros] = results[i] + 1;
                        openNodes.add(nextZeros);
                    }
                }
            }
            currentNodes.clear();
            for (int k: openNodes) {
                currentNodes.add(k);
            }
            openNodes.clear();
        }
        return (-1);
    
        //int res;
	// 毎回ここが呼び出されますので、ここに答えを返す関数の中身を記載してください。
//        if (A == 0) return 0; //動かす必要のない時
//        if (A + B < K) return -1; //ひっくり返せない時
//        int[] array = new int[A + B + 1];
//        for (int i = 0; i <= A + B; i++) array[i] = -1;
//        List<int> nownode = new List<int>();
//        List<int> nextnode = new List<int>();
//        nownode.Add(A);
//        array[A] = 0;
//        while (nownode.Count > 0)
//        {
//            foreach (int i in nownode) //iは0の数
//            {
//                for (int j = Math.Max(0, K - (A + B - i)); j <= Math.Min(i, K); j++) //jは0をひっくり返す数
//                {
//                    int nextzero = i + (K - 2 * j); //遷移する次の状態の0の数
//                    if (array[nextzero] == -1)  //初めて到達する地点であれば、次の探索に加える
//                    {
//                        if (nextzero == 0) return array[i] + 1; //答えが見つかれば、それを返す
//                        array[nextzero] = array[i] + 1;
//                        nextnode.Add(nextzero);
//                    }
//                }
//            }
//            //次のターン用にnextをnowに
//            nownode.Clear();
//            foreach (int k in nextnode) nownode.Add(k);
//            nextnode.Clear();
//        }
//        return -1;
    }

// ここから、一番下の「ここまで」という部分まではテスト用となりますので、
// 提出時は削除をしてください。
    public static void main(String[] args) {
        try {
            eq(0,(new BinaryFlips()).minimalMoves(3, 0, 3),1);
            eq(1,(new BinaryFlips()).minimalMoves(4, 0, 3),4);
            eq(2,(new BinaryFlips()).minimalMoves(4, 1, 3),2);
            eq(3,(new BinaryFlips()).minimalMoves(3, 2, 5),-1);
            eq(4,(new BinaryFlips()).minimalMoves(100000, 100000, 578),174);
            eq(5,(new BinaryFlips()).minimalMoves(0, 0, 1),0);
            eq(6,(new BinaryFlips()).minimalMoves(4, 44, 50),-1);
            eq(7,(new BinaryFlips()).minimalMoves(99200, 0, 99101),1004);
            eq(8,(new BinaryFlips()).minimalMoves(99999, 100000, 50000),-1);
            eq(9,(new BinaryFlips()).minimalMoves(1, 99999, 99999),99999);
        } catch( Exception exx) {
            System.err.println(exx);
            exx.printStackTrace(System.err);
        }

        System.out.println("Hello, World!" + Math.PI);
        // http://java.sun.com/javase/ja/6/docs/ja/api/java/lang/Math.html
        System.out.println("d: " + Math.max(1, 2) + ", " + Math.min(3, 4));
        // 配列
        // http://www.javaroad.jp/java_array1.htm
        int array[] = new int[10];
        int coins[] = { 1, 5, 10, 50, 100, 500 };
        for (int i: coins) {
            System.out.println("d0: " + i);
        }
        for (int i = 0; i < coins.length; i ++) {
            System.out.println("d1: " + coins[i]);
        }
        // generics
        List<String> coins2 = new ArrayList<String>();
        coins2.add(String.valueOf("one"));
        coins2.add(String.valueOf("five"));
        coins2.add(String.valueOf("ten"));
        coins2.add(String.valueOf("fifty"));
        coins2.add(String.valueOf("hundred"));
        coins2.add(String.valueOf("fivehundred"));
        for (String s: coins2) {
            System.out.println("d2: " + s);
        }
        // java.util package の collections framework

    }
    private static void eq( int n, int a, int b ) {
        if ( a==b )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected "+b+", received "+a+".");
    }
// ここまで
}
