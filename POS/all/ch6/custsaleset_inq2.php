<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
    include("mysqlcntdb.php");	
//---------- �N product �� saty ���X----------
	$SQLStr = "SELECT cust.*, saty.*  FROM cust AS cust ";	
	$SQLStr .= "LEFT JOIN saty AS saty ON cust.custprictype = saty.satyno WHERE custno='$custno'";	
	$res = mysql_query($SQLStr);
	
//---------- ���X saty ��ƪ�������----------
	$SQLStr2 = "SELECT * FROM saty";
	$res2 = mysql_query($SQLStr2);
	
//---------- �P�_�d�ߵ��G�O�_����----------
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>


<!------ �ǵ� index.php �ɮ� ------>
<form name="form1" method="post" action="../index.php?Select=10">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" bgcolor="#FFFFFF" >
    <tr bgcolor="#FFFFFF"> 
      <td >  
        <table width="400" border="0" align="center" >
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">�Ȥ�P��]�w</font>
            </td>            
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="�j�M�Ȥ�P��]�w����,�^����">
            </td>
	  </tr>
  </table>
  
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr>           
            <td width="152" align="center">�Ȥ�Ǹ�</td>
            <td align="left" colspan="3"><?=$row[custno]?>		        
            </td>
		  </tr>	
          <tr>           
            <td width="152" align="center">�Ȥ����O</td>
            <td width="233" align="left"><?=$row['custtype']?>
		        
            </td>
            <td width="120" align="center">�Ȥ�²��</td>
            <td width="252" align="left"><?=$row['custsname']?>             
            </td>
          </tr>
          <tr> 
            <td width="152" align="center">�Ȥ�W��</td>
            <td width="233" align="left"><?=$row['custname']?>               
            </td>
            <td width="120" align="center">�t�d�H</td>
            <td width="252" align="left"><?=$row['custleader']?>             
          </tr>
          <tr>
            <td width="152" align="center">�Τ@�s��</td>
            <td width="233" align="left"><?=$row['custinvoice']?>               
            </td>
            <td width="120" align="center">�p���H</td>
            <td width="252" align="left"><?=$row['custcontact']?>               
            </td>
          </tr>		  
		 <tr>
			<td width="152" height="22" align="center">���q�a�}</td>
            <td width="233" height="22"><?=$row['custadr']?>                
            </td>           
          </tr>
		  <tr>
			<td width="152" height="22" align="center">���b��</td>
            <td width="233" height="22"> 
			   <?=substr($row['custclosdate'],0,10)?>
            </td>           
          </tr>
		  <tr>
			<td width="152" height="22" align="center">�P�����O</td>
            <td width="233" height="22"><?=$row['custprictype']?><?=$row['satyname']?>  
            </td>           
          </tr>
		  <tr> 
            <td width="152" align="center">�ꦬ���</td>
            <td width="233"><?=$row['custpricper']?></td>
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