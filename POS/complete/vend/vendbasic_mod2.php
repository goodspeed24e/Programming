<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?
    include("mysqlcntdb.php");	
//---------- �N vend �� vety ���X�_��---------- 		
	$SQLStr = "SELECT vend.*, vety.* FROM vend AS vend ";
	$SQLStr .= "LEFT JOIN vety AS vety ON vend.vendtype = vety.vetyno WHERE vendno='$vendno'";
	$res = mysql_query($SQLStr);
	$SQLStr2 = "SELECT * FROM vety";
	$res2 = mysql_query($SQLStr2);
 //--------------------------- �P�_�d�ߵ��G�O�_����---------------------------		
	if (mysql_num_rows($res)>0)	
	{
	$row = mysql_fetch_array($res);
?>
<!----�ק�t�Ӹ��,�i�Jvendbasic_mod3.php,�s����Ʈw  ----->
<form name="form1" method="post" action="vendbasic_mod3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td bgcolor="#FFFFff">  
        <table width="770" border="0" align="center">
          <tr> 
            <td width="60%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">�t�ӸԲӸ�T</font>
            </td>          
            <td align="center"> 
              <input type="submit" name="submit" value="�ק�t�Ӹ��">
            </td>
	  </tr>
        </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
		   <tr> 
            <td width="86" align="center">�t�ӽs��</td>
            <td width="209" align="left" colspan="3"><?=$row[vendno]?>
                <input  type="hidden" name="vendno" size="10" value="<?=$row[vendno]?>">
            </td>
          
          </tr>
          <tr>           
            <td width="86" align="center">�t�����O</td>
            <td width="209" align="left"> 
<?
 		$num = mysql_num_rows($res2);

//------------------------------�e�{�t�����O���W��------------------------------- 
                echo "<select name='vendtype'>";
		echo "<option value='" . $row['vetyno'] . "'>" . $row['vetyname'] . "</option>";
		for ($i=0;$i<$num;$i++)
		{
		  $row2 = mysql_fetch_array($res2);
	          echo "<option value='" . $row2['vetyno'] . "'>" . $row2['vetyname'] . "</option>";
		}
                echo "</select>";
		
?>
		<input type="hidden" name="vendno" size="10" value="<?=$row['vendno']?>">
            </td>
            <td width="85" align="center">�t��²��</td>
            <td width="201" align="left">
                <input type="text" name="vendsname" size="30" value="<?=$row['vendsname']?>">
            </td>
          </tr>
          <tr> 
            <td width="86" align="center">�t�ӦW��</td>
            <td width="209" align="left">
                <input type="text" name="vendname" size="40" value="<?=$row['vendname']?>">
            </td>
            <td width="85" align="center">�t�d�H</td>
            <td width="201" align="left">
                <input type="text" name="vendleader" size="10" value="<?=$row['vendleader']?>">
            </td>
          </tr>
          <tr>
            <td width="86" align="center">�Τ@�s��</td>
            <td width="209" align="left">
                <input type="text" name="vendinvoice" size="10" value="<?=$row['vendinvoice']?>">
            </td>
            <td width="85" align="center">�p���H</td>
            <td width="201" align="left">
                <input type="text" name="vendcontact" size="10" value="<?=$row['vendcontact']?>">
            </td>
          </tr>
          <tr>
            <td width="86" height="22" align="center">�p���q��</td>
            <td width="209" height="22" align="left">
                <input type="text" name="vendtel" size="10" value="<?=$row['vendtel']?>">
            </td>
            <td width="85" height="22" align="center">�p�����</td>
            <td width="201" height="22" align="left">
                <input type="text" name="vendmobil" size="10" value="<?=$row['vendmobil']?>">
            </td>
          </tr>
          <tr>            
            <td width="86" height="22" align="center">�ǯu��</td>
            <td width="209" height="22" align="left">
                <input type="text" name="vendfax" size="10" value="<?=$row['vendfax']?>">
            </td>
			<td width="85" height="22" align="center">�~�ȭ�</td>
            <td width="201" height="22" align="left">
                <input type="text" name="vendsales" size="10" value="<?=$row['vendsales']?>">
            </td>           
          </tr>
		 <tr>
			<td width="103" height="22" align="center">���q�a�}</td>
            <td width="187" height="22"> 
                <input type="text" name="vendadr" size="40" value="<?=$row['vendadr']?>">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�e�f�a�}</td>
            <td width="187" height="22"> 
                <input type="text" name="vendpradr" size="40" value="<?=$row['vendpradr']?>">
            </td>           
          </tr>
		  <tr>
			<td width="103" height="22" align="center">�o���a�}</td>
            <td width="187" height="22"> 
                <input type="text" name="vendinadr" size="40" value="<?=$row['vendinadr']?>">
            </td>           
          </tr>
		  <tr> 
            <td width="103" align="center">�q�l�H�c</td>
            <td width="187"> 
                <input type="text" name="vendemail" size="40" value="<?=$row['vendemail']?>">
            </td>
		  </tr>
		  <tr> 
            <td width="96" align="center">���}</td>
            <td width="351"> 
                <input type="text" name="vendhttp" size="40" value="<?=$row['vendhttp']?>">
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
