<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>銷售類別列印</title>
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

	// ----------取出現有銷售類別----------	
	$SQLStr = "SELECT * FROM saty";	
	$res = mysql_query($SQLStr);
	//---------- 取出現有銷售類別 ----------		
	
?>

<form name="form1" method="post" action="./index.php?$Select=65">
  <table width="608" border="0" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td width="604" > 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" align="center"> 
             <font bgcolor="#0000CC">列印銷售類別</font>
            </td>           
          </tr>
        </table>
  <table width="600" border="0" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="600" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">現有銷售類別代碼</td>
			<td bgcolor="#CCCCCC" align="center">現有銷售類別名稱</td>
          </tr>
<?
	//---------- 取出所有銷售類別名稱並呈現於網頁上----------
	$sql="select * from saty ";
    $rows=mysql_query($sql);
    while(list($satyno , $satyname )=@mysql_fetch_row($rows)) {
        echo "
             <tr bgcolor='#F7F7F7'>
                <td><font size='-1'>$satyno</font></td>
                <td><font size='-1'>$satyname</font></td>                
              </tr>
            ";
    }
	//---------- 取出所有銷售類別名稱並呈現於網頁上----------
?>    
	   </table>
      </td>
    </tr>
 </table>
 
</form>
</body>
