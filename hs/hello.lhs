#!/usr/bin/env runhugs
-*- coding: utf-8 -*-

>module Main where
>import System

>main = do av <- getArgs
>          putStrLn $ "Hello, " ++ (av !! 0) ++ "!"
