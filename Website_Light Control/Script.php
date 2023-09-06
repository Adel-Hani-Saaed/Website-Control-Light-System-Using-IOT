<?php

if (isset($_GET['status']))                 //Check of the retuen parameter
{       
    
    /*Open the file*/
    $Myfile = fopen("status.txt","w");

    if ($_GET['status'] == 'on' )           //$_GET[' ']-->> is array Assosiation
    {
        fwrite($Myfile , "1");              //open the file and write the value 1
        header("Location: on.html");        //Go to the file.html is name on.html
    }

    elseif($_GET['status'] == 'off')
    {
        fwrite($Myfile , "0");              //open the file and update the overwritten the value 0
        header("Location: off.html");
    }

    /* Closed the file  */
    fclose($Myfile);
}
?>