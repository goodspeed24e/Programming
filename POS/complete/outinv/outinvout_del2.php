<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�L���D���</title>
</head>
<body>
<?
    include("mysqlcntdb.php");
	//----------�N product �� outinv ���X,���X�ŦX���󪺩Ҧ��i�f�����---------
	$SQLStr = "SELECT outinv.*, product.* FROM outinv AS outinv ";
	$SQLStr .= "LEFT JOIN  product AS  product ON outinv.outiprodno = product.prodno WHERE (outino='$outino' and outiprodno='$outiprodno')";
	$res = mysql_query($SQLStr);		
	//---------- �P�_�d�ߵ��G�O�_����--------------------------
	if (mysql_num_rows($res)>0)	
	{
	$row = mysql_fetch_array($res);
?>
<!------ �ǵ� outinvout_del3.php �ɮ�  ------>
<form name="form1" method="post" action="outinvout_del3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
      <td  bgcolor="#FFFFFF"> 
        <table width="400" border="0" align="center">
          <tr> 
            <td width="100%" bgcolor="#9933FF" align="center"><font color="#FFFFFF">�P�f�ԲӸ�T</font>
            </td>                
          </tr>
	</table>
	<table width="770">
	  <tr>
            <td align="center"> 
              <input type="submit" name="submit" value="�R���P�f���">
            </td>
	  </tr>
  </table>
  <!--�e�{�P�f���,�ѧP�_----------> 
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" >
          <tr>           
            <td width="241" align="center"><font >�P�f�渹</font></td>
            <td width="522" align="left"><?=$row['outino']?> 
		      <input  type="hidden" name="outino" size="10" value="<?=$row['outino']?>">
            </td>            
          </tr>
          <tr> 
            <td width="241" align="center"><font >���~�s��</font></td>
            <td width="522" align="left"><?=$row['outiprodno']?>
			    <input type="hidden" name="outiprodno" size="10" value="<?=$row['outiprodno']?>">
            </td>
          </tr>
		  <tr> 
            <td width="241" align="center"><font >���~�W��</font></td>
            <td width="522" align="left"><?=$row['prodname']?>			   		   
            </td>
          </tr>         
          <tr>
            <td width="241" height="22" align="center"><font >�P�f���</font> </td>
            <td width="522" height="22" align="left"><?=$row['outidate']?>               
            </td>            
          </tr>
          <tr>            
            <td width="241" height="22" align="center">�Ȥ�s��</td>
            <td width="522" height="22" align="left"><?=$row['outicustno']?>
			<input type="hidden" name="outicustno" size="10" value="<?=$row['outicustno']?>"> 			
            </td>			           
          </tr>
		  <tr>            
            <td width="241" height="22" align="center">�����渹</td>
            <td width="522" height="22" align="left"><?=$row['outipono']?>
			<input type="hidden" name="outicustno" size="10" value="<?=$row['outipono']?>">
			</td>			           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">���~�ƶq</td>
            <td width="522" height="22"><?=$row['outiprodqty']?>
			<input type="hidden" name="outiprodqty" size="6" value="<?=$row['outiprodqty']?>">                 
            </td>           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">���~���</td>
            <td width="522" height="22"><?=$row['outiunit']?>           
            </td>           
          </tr>
		  <tr> 
            <td width="241" align="center">���</td>
            <td width="522"><?=$row['outipric']?>
			<input type="hidden" name="outipric" size="6" value="<?=$row['outipric']?>">                   
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
	 $msg="�L���P�f��";
	 include("windowsclose.php");		
	}
?>
</body>
</html>