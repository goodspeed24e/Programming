<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>產品單位代碼列印</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<body  onLoad="window.print()">
<?php
    //----------連接資料庫----------
	include("mysqlcntdb.php");
	//----------連接資料庫----------

	// ----------取出現有產品單位代碼----------	
	$SQLStr = "SELECT * FROM prun";	
	$res = mysql_query($SQLStr);
	//---------- 取出現有產品單位代碼 ----------		
	
?>

<form name="form1" method="post" action="./index.php?$Select=65">
  <table width="608" border="0" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td width="604" > 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" align="center"> 
             <font bgcolor="#0000CC">列印產品產品單位代碼</font>
            </td>           
          </tr>
        </table>
  <table width="600" border="0" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="600" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">現有產品產品單位代碼</td>
			<td bgcolor="#CCCCCC" align="center">現有產品產品單位代碼</td>
          </tr>
<?
	//---------- 取出所有產品產品單位並呈現於網頁上----------
	$sql="select * from prun ";
    $rows=mysql_query($sql);
    while(list($prunno , $prunname )=@mysql_fetch_row($rows)) {
        echo "
             <tr bgcolor='#F7F7F7'>
                <td><font size='-1'>$prunno</font></td>
                <td><font size='-1'>$prunname</font></td>                
              </tr>
            ";
    }
	//---------- 取出所有產品產品單位代碼並呈現於網頁上----------
?>    
	   </table>
      </td>
    </tr>
 </table>
 
</form>
</body>
