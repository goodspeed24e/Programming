<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
    include("mysqlcntdb.php");	
//---------- �N cust �� saty ���X�_��---------- 
	$SQLStr = "SELECT cust.*, saty.*  FROM cust AS cust ";
	$SQLStr .= "LEFT JOIN saty AS saty ON cust.custprictype = saty.satyno WHERE custno='$custno'";	
	$res = mysql_query($SQLStr);

//---------- ���X saty ��ƪ�������---------------------- 
	$SQLStr2 = "SELECT * FROM saty";
	$res2 = mysql_query($SQLStr2);
	
//---------- �P�_�d�ߵ��G�O�_����-----------------------------------
	if (mysql_num_rows($res)>0) 	
	{
	$row = mysql_fetch_array($res);
?>
<!------ �ǵ� mod3.php �ɮ�,��s��Ʈw  ------>
<form name="form1" method="post" action="custsaleset_mod3.php?custno='$custno'">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="770" border="0" align="center">
          <tr> 
            <td width="50%" bgcolor="#9933FF"     align="center"><font color="#FFFFFF">�Ȥ�P��]�w</font>
            </td>     
            <td align="center"> 
              <input type="submit" name="submit" value="�ק�Ȥ�P��]�w">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr>           
            <td width="86" align="center">�Ȥ�Ǹ�</td>
            <td width="209" align="left" colspan="3"><?=$row[custno]?>
			 <input  type="hidden" name="custno" size="10" value="<?=$row['custno']?>">
          </tr>
          <tr> 
          <tr>           
            <td width="86" align="center">�Ȥ����O</td>
            <td width="209" align="left"><?=$row['custtype']?>
		        
            </td>
            <td width="85" align="center">�Ȥ�²��</td>
            <td width="201" align="left"><?=$row['custsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="86" align="center">�Ȥ�W��</td>
            <td width="209" align="left"><?=$row['custname']?>               
            </td>
            <td width="96" align="center">�t�d�H</td>
            <td width="201" align="left"><?=$row['custleader']?>             
          </tr>
          <tr>
            <td width="86" align="center">�Τ@�s��</td>
            <td width="209" align="left"><?=$row['custinvoice']?>               
            </td>
            <td width="96" align="center">�p���H</td>
            <td width="201" align="left"><?=$row['custcontact']?>               
            </td>
          </tr>
		  
		 <tr>
			<td width="86" height="22" align="center">���q�a�}</td>
            <td width="187" height="22"><?=$row['custadr']?>                
            </td>           
          </tr>
		</table>
		<br>
		<table bgcolor="#FFCC33" cellpadding="0" cellspacing="0" width="770"> 
		  <tr>
			<td width="111" height="22" align="center">���b��</td>
            <td width="268" height="22" > 
			   <input type="text" name="custclosdate" size="10"  value="<?=$row['custclosdate']?>">
            </td>
			<td width="131" height="22" align="center">�P�����O</td>
            <td width="258" height="22" > 
<?
 		$num = mysql_num_rows($res2);

//--------------------- �e�{�P�����O���W��-------------------------------- 
                echo "<select name='custprictype'>";
		echo "<option value='" . $row['satyno'] . "'>" . $row['satyname'] . "</option>";
		for ($i=0;$i<$num;$i++)
		{
		  $row2 = mysql_fetch_array($res2);
	          echo "<option value='" . $row2['satyno'] . "'>" . $row2['satyname'] . "</option>";
		}
                echo "</select>";		
?>
<?=$row2['custprictype']?>
</td>           
          </tr>
		  <tr> 
            <td width="111" align="center">�ꦬ���</td>
            <td width="268" > 
                <input type="text" name="custpricper" size="3" value="<?=$row['custpricper']?>">
            </td>
		</tr>
  </table>
</form>
<?
}
else
	{
	 $msg="�L���Ȥ�";
	 include("windowsclose.php");		
	}
?>
</body>
</html>
