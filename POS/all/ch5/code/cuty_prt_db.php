<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>���O�C�L</title>
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

	// ----------���X�{�����O----------	
	$SQLStr = "SELECT * FROM cuty";	
	$res = mysql_query($SQLStr);
	//---------- ���X�{�����O ----------		
	
?>

<form name="form1" method="post" action="./index.php?$Select=65">
  <table width="608" border="0" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td width="604" > 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" align="center"> 
             <font bgcolor="#0000CC">�C�L�Ȥ����O</font>
            </td>           
          </tr>
        </table>
  <table width="600" border="0" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="600" border="1" cellspacing="0" bgcolor="#FFFFFF">
          <tr> 
            <td bgcolor="#CCCCCC" align="center">�{���Ȥ����O�N�X</td>
			<td bgcolor="#CCCCCC" align="center">�{���Ȥ����O�W��</td>
          </tr>
<?
	//---------- ���X�Ҧ��Ȥ����O�W�٨çe�{������W----------
	$sql="select * from cuty ";
    $rows=mysql_query($sql);
    while(list($cutyno , $cutyname )=@mysql_fetch_row($rows)) {
        echo "
             <tr bgcolor='#F7F7F7'>
                <td><font size='-1'>$cutyno</font></td>
                <td><font size='-1'>$cutyname</font></td>                
              </tr>
            ";
    }
	//---------- ���X�Ҧ��Ȥ����O�W�٨çe�{������W----------
?>    
	   </table>
      </td>
    </tr>
 </table>
 
</form>
</body>
