<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>���O�s�W</title>
<style type="text/css">
<!--
.style1 {color: #FF0000}
-->
</style>
</head>
<?php
    //----------�s����Ʈw----------
	include("mysqlcntdb.php");
	//----------�s����Ʈw----------
if ($func == add) 
	{
		//---------- �N���O�s�W�ܸ�Ʈw��----------
		$SQLStr = "INSERT INTO cuty (cutyno, cutyname) VALUES('cutyno', '$cutyname')";
		mysql_query("SET NAMES 'big5'");
        mysql_query("SET CHARACTER SET big5"); 
		mysql_query($SQLStr);
		//---------- �N���O�s�W�ܸ�Ʈw�� ----------
	}

	// ----------���X�{�����O----------	
	$SQLStr = "SELECT * FROM cuty";	
	$res = mysql_query($SQLStr);
	//---------- ���X�{�����O ----------		
	
?>

<form name="form1" method="post" action="./code/cuty_add_db.php">
  <table width="750" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr> 
      <td bgcolor="#CCFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#CCFFFF" align="center"> 
             <font bgcolor="#0000CC">�s�W�Ȥ����O</font>
            </td>           
          </tr>
        </table>
  <table width="750" border="1" cellspacing="0" cellpadding="0" bordercolor="#9999FF">
    <tr>
      <td>
        <table width="750" border="1" cellspacing="0" bgcolor="#FFFFFF">
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
 <table width="400" border="0" align="center">          
          <tr > 
            <td bgcolor="#0000CC" align="center" ><font color="#FFFFFF">���O</font>  
                <input type="text" name="cutyno">
				<input type="text" name="cutyname">
                <input type="submit" name="Submit" value="�s�W">
            </td>
			
          </tr> 
	 </table>        
</table>
</form>

