<?

class Matrix {
  function Matrix ($nRow, $nCol) {
    $this->nRow = $nRow;
    $this->nCol = $nCol;
    $this->pn[] = 0;
  }
  function set ($iRow, $iCol, $n) {
    $this->pn[($iRow * $this->nCol) + $iCol] = $n;
  }
  function get ($iRow, $iCol) {
    return ($this->pn[($iRow * $this->nCol) + $iCol]);
  }
  function show () {
    for ($iRow = 0; $iRow < $this->nRow; $iRow ++) {
      $pszDelim = "";
      for ($iCol = 0; $iCol < $this->nCol; $iCol ++) {
        printf("%s%3d", $pszDelim, $this->get($iRow, $iCol));
        $pszDelim = " ";
      }
      echo "\n";
    }
  }
};

function mult (&$pmatrixA, &$pmatrixB) {
  $pmatrixC = new Matrix($pmatrixA->nRow, $pmatrixB->nCol);
  for ($iRow = 0; $iRow < $pmatrixC->nRow; $iRow ++) {
    for ($iCol = 0; $iCol < $pmatrixC->nCol; $iCol ++) {
      $pmatrixC->set($iRow, $iCol, 0);
      for ($i = 0; $i < $pmatrixA->nCol; $i ++) {
        $pmatrixC->set($iRow, $iCol, $pmatrixC->get($iRow, $iCol) +
         $pmatrixA->get($iRow, $i) * $pmatrixB->get($i, $iCol) );
      }
    }
  }
  return ($pmatrixC);
}

?><html><body><pre><?

$pmatrixA = new Matrix(500, 500);
for ($iRow = 0; $iRow < $pmatrixA->nRow; $iRow ++) {
  for ($iCol = 0; $iCol < $pmatrixA->nCol; $iCol ++) {
    $pmatrixA->set($iRow, $iCol, $iRow + $iCol + 1);
  }
}
echo "A =\n";
//$pmatrixA->show();

$pmatrixB = new Matrix(500, 500);
for ($iRow = 0; $iRow < $pmatrixB->nRow; $iRow ++) {
  for ($iCol = 0; $iCol < $pmatrixB->nCol; $iCol ++) {
    $pmatrixB->set($iRow, $iCol, $iRow + $iCol + 1);
  }
}
echo "B =\n";
//$pmatrixB->show();


$pmatrixC = mult($pmatrixA, $pmatrixB);
echo "C =\n";
//$pmatrixC->show();

?></pre></body></html><?

?>
