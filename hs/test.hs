module Main (main) where

strToInt :: String -> Integer
strToInt s = (read :: String -> Integer) s

main = do putStr "x = "
          x <- getLine
          putStr "y = "
          y <- getLine
          putStr ("x + y = " ++ show ((strToInt x) + (strToInt y)))

--foo x = bar + x
--bar = 2
--
---- module Test where
---- 
---- len [] = 0
---- len (x:xs) = 1 + len xs
