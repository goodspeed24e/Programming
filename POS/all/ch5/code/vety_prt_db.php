<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�t�����O�C�L</title>
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

	// ----------���X�{���t�����O----------	
	$SQLStr = "SELECT * FROM vety";	
	$res = mysql_query($SQLStr);
	//---------- ���X�{���t�����O ----------		
	
?>

<form name="form1" method="post" action="./index.php?$Select=65">
  <table width="608" border="0" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td width="604" > 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" align="center"> 
             <font bgcolor="#0000CC">�C�L�t�����O</font>
            </td>           
          </tr>
        </table>
  <table width="600" border="0" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="600" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">�{���t�����O�N�X</td>
			<td bgcolor="#CCCCCC" align="center">�{���t�����O�W��</td>
          </tr>
<?
	//---------- ���X�Ҧ��t�����O�W�٨çe�{������W----------
	$sql="select * from vety ";
    $rows=mysql_query($sql);
    while(list($vetyno , $vetyname )=@mysql_fetch_row($rows)) {
        echo "
             <tr bgcolor='#F7F7F7'>
                <td><font size='-1'>$vetyno</font></td>
                <td><font size='-1'>$vetyname</font></td>                
              </tr>
            ";
    }
	//---------- ���X�Ҧ��t�����O�W�٨çe�{������W----------
?>    
	   </table>
      </td>
    </tr>
 </table>
 
</form>
</body>
