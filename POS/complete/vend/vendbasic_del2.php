<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
// -------------���X�Ҧ��t�Ӥγs���t�����O�����---------------
    include("mysqlcntdb.php");	
	$SQLStr = "SELECT vend.*, vety.* FROM vend AS vend ";
	$SQLStr .= "LEFT JOIN vety AS vety ON vend.vendtype = vety.vetyno WHERE vendno='$vendno'";
	$res = mysql_query($SQLStr);	
	$SQLStr2 = "SELECT * FROM vety";
	$res2 = mysql_query($SQLStr2);	
//----------------- �P�_�d�ߵ��G�O�_����----------------
	if (mysql_num_rows($res)>0) 
	{
	$row = mysql_fetch_array($res);
?>
<!----�R���t�Ӹ��,�i�Jvendbasic_del3.php,�s����Ʈw  ----->
<form name="form1" method="post" action="vendbasic_del3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF">  
        <table width="770" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">�t�ӸԲӸ�T</font>
            </td>
            <td align="center"> 
              <input type="submit" name="submit" value="�R���t�Ӹ��">
            </td>
	  </tr>
        </table>
<!---//---------------	�קﶵ��----------------------->            	
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		  <tr> 
            <td width="86" align="center">�t�ӽs��</td>
            <td width="209" align="left" colspan="3"><?=$row[vendno]?>
                <input  type="hidden" name="vendno" size="10" value="<?=$row[vendno]?>">
            </td>          
          </tr>
          <tr>           
            <td width="86" align="center">�t�����O</td>
            <td width="209" align="left"><?=$row[vendtype]?>
            </td>
            <td width="85" align="center">�t��²��</td>
            <td width="201" align="left"><?=$row['vendsname']?>              
            </td>
          </tr>
          <tr> 
            <td width="86" align="center">�t�ӦW��</td>
            <td width="209" align="left"><?=$row['vendname']?>              
            </td>
            <td width="85" align="center">�t�d�H</td>
            <td width="201" align="left"><?=$row['vendleader']?>              
            </td>
          </tr>
          <tr>
            <td width="86" align="center">�Τ@�s��</td>
            <td width="209" align="left"><?=$row['vendinvoice']?>              
            </td>
            <td width="85" align="center">�p���H</td>
            <td width="201" align="left"><?=$row['vendcontact']?>             
            </td>
          </tr>
          <tr>
            <td width="86" height="22" align="center">�p���q��</td>
            <td width="209" height="22" align="left"><?=$row['vendtel']?>              
            </td>
            <td width="85" height="22" align="center">�p�����</td>
            <td width="201" height="22" align="left"><?=$row['vendmobil']?>              
            </td>
          </tr>
          <tr>            
            <td width="86" height="22" align="center">�ǯu��</td>
            <td width="209" height="22" align="left"><?=$row['vendfax']?>              
            </td>
			<td width="85" height="22" align="center">�~�ȭ�</td>
            <td width="201" height="22" align="left"><?=$row['vendsales']?>                
            </td>           
          </tr>
		 <tr>
			<td width="103" height="22" align="center">���q�a�}</td>
            <td width="187" height="22"><?=$row['vendadr']?>              
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�e�f�a�}</td>
            <td width="187" height="22"><?=$row['vendpradr']?>              
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�o���a�}</td>
            <td width="187" height="22"><?=$row['vendinadr']?>             
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">�q�l�H�c</td>
            <td width="187"><?=$row['vendemail']?>              
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">���}</td>
            <td width="351"><?=$row['vendhttp']?>             
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
	 $msg="�L���t��";
	 include("windowsclose.php");		
	}
?>
</body>
</html>
