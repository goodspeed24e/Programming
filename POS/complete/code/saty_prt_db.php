<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�P�����O�C�L</title>
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

	// ----------���X�{���P�����O----------	
	$SQLStr = "SELECT * FROM saty";	
	$res = mysql_query($SQLStr);
	//---------- ���X�{���P�����O ----------		
	
?>

<form name="form1" method="post" action="./index.php?$Select=65">
  <table width="608" border="0" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td width="604" > 
        <table width="400" border="0" align="center">		 
          <tr> 
            <td width="100%" align="center"> 
             <font >�P�����O��</font>
            </td>           
          </tr>
        </table>
  <table width="600" border="0" cellspacing="0" cellpadding="0" >
    <tr>
      <td>
        <table width="600" border="0" cellspacing="0" >
		  <tr> 
            <td  align="left" colspan="2"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>   
          <tr> 
            <td  align="left">�P�����O�N�X</td>
			<td  align="left">�P�����O�W��</td>
          </tr>
		  <tr> 
            <td  align="left" colspan="2"> 
              <hr  size="1" color="#000000"  width="100%">
            </td>
          </tr>   
<?
	//---------- ���X�Ҧ��P�����O�W�٨çe�{������W----------
	$sql="select * from saty ";
    $rows=mysql_query($sql);
    while(list($satyno , $satyname )=@mysql_fetch_row($rows)) {
        echo "
             <tr >
                <td align='left'><font size='-1'>$satyno</font></td>
                <td align='left'><font size='-1'>$satyname</font></td>                
              </tr>
            ";
    }
	//---------- ���X�Ҧ��P�����O�W�٨çe�{������W----------
?>    
	   </table>
      </td>
    </tr>
 </table>
 
</form>
</body>
