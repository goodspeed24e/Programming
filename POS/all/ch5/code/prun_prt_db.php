<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>���~���N�X�C�L</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<body  onLoad="window.print()">
<?php
    //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw----------

	// ----------���X�{�����~���N�X----------	
	$SQLStr = "SELECT * FROM prun";	
	$res = mysql_query($SQLStr);
	//---------- ���X�{�����~���N�X ----------		
	
?>

<form name="form1" method="post" action="./index.php?$Select=65">
  <table width="608" border="0" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td width="604" > 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" align="center"> 
             <font bgcolor="#0000CC">�C�L���~���~���N�X</font>
            </td>           
          </tr>
        </table>
  <table width="600" border="0" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="600" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">�{�����~���~���N�X</td>
			<td bgcolor="#CCCCCC" align="center">�{�����~���~���N�X</td>
          </tr>
<?
	//---------- ���X�Ҧ����~���~���çe�{������W----------
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
	//---------- ���X�Ҧ����~���~���N�X�çe�{������W----------
?>    
	   </table>
      </td>
    </tr>
 </table>
 
</form>
</body>
