module Main where
import System
main = do av <- getArgs
          putStrLn $ "Hi, " ++ (av !! 0) ++ "!"
