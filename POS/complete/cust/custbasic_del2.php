<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
    include("mysqlcntdb.php");
	
//---------- �N cust �� cuty ���X�_��---------- 
	$SQLStr = "SELECT cust.*, cuty.* FROM cust AS cust ";
	$SQLStr .= "LEFT JOIN cuty AS cuty ON cust.custtype = cuty.cutyno WHERE custno='$custno'";
	$res = mysql_query($SQLStr);	
	
//---------- ���X cuty ��ƪ�������---------- 
	$SQLStr2 = "SELECT * FROM cuty";
	$res2 = mysql_query($SQLStr2);	
	
//---------- �P�_�d�ߵ��G�O�_����----------------
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>

<!------ �ǵ� custbasic_act.php �ɮ�  ------>
<form name="form1" method="post" action="custbasic_act.php?func=del">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="400" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">�Ȥ�ԲӸ�T</font>
            <td align="center"> 
              <input type="submit" name="submit" value="�R���Ȥ���">
            </td>
	  </tr>
        </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		  <tr> 
            <td width="86" align="center">�Ȥ�Ǹ�</td>
            <td width="209" align="left"><?=$row[custno]?>
                <input  type="hidden" name="custno" size="10" value="<?=$row[custno]?>">
            </td>
            <td width="85" align="center">�Τ@�s��</td>
            <td width="201" align="left"><?=$row['custinvoice']?>            
            </td>
          </tr>
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
            <td width="85" align="center">�t�d�H</td>
            <td width="201" align="left"><?=$row['custleader']?>           
            </td>
          </tr>
          <tr>
            <td width="86" align="center">�~�ȭ�</td>
            <td width="209" align="left"><?=$row['custsales']?>             
            </td>
            <td width="85" align="center">�p���H</td>
            <td width="201" align="left"><?=$row['custcontact']?>              
            </td>
          </tr>
          <tr>
            <td width="86" height="22" align="center">�p���q��</td>
            <td width="209" height="22" align="left"><?=$row['custtel']?>             
            </td>
            <td width="85" height="22" align="center">�p�����</td>
            <td width="201" height="22" align="left"><?=$row['custmobil']?>          
            </td>
          </tr>
          <tr>            
            <td width="86" height="22" align="center">�ǯu��</td>
            <td width="209" height="22" align="left"><?=$row['custfax']?>              
            </td>			     
          </tr>
		 <tr>
			<td width="103" height="22" align="center">���q�a�}</td>
            <td width="187" height="22"><?=$row['custadr']?>
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�e�f�a�}</td>
            <td width="187" height="22"><?=$row['custpradr']?>               
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�o���a�}</td>
            <td width="187" height="22"><?=$row['custinadr']?>              
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">�q�l�H�c</td>
            <td width="187"> <?=$row['custemail']?>             
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">���}</td>
            <td width="351"><?=$row['custhttp']?>               
            </td>
          </tr>    
		</td>
    </tr> 
  </table>
</form>
<?
}
else
	{
	 $msg="�L���Ȥ���";
	 include("windowsclose.php");		
	}
?>
</body>
</html>
