<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�ק�P�f���</title>
</head>
<body>
<?
    include("mysqlcntdb.php");	
	//----------���X �i�f�β��~���,�N product �� outinv ���X---------	
	$SQLStr = "SELECT outinv.*, product.* FROM outinv AS outinv ";
	$SQLStr .= "LEFT JOIN  product AS  product ON outinv.outiprodno = product.prodno WHERE (outino='$outino' and outiprodno='$outiprodno')";
	$res = mysql_query($SQLStr);
	//------- �P�_�j�M���G�O�_����------
	if (mysql_num_rows($res)>0)	
	{
	$row = mysql_fetch_array($res);
?>
<script language="JavaScript">
//-------------- �ˬd���~�ƶq--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("���~�ƶq�ť�");
      fld.focus();
      fld.select();
   }
}
//-------------- �ˬd���~���--------------
function checkpric(fld){
   if (fld.value == ""){
      alert("���~�����쬰�ť�");
      fld.focus();
      fld.select();
   }
}
</script>
<?php $oqty=$row['outiprodqty'];  
       $opric=$row['outipric']; 
       $ocust=$row['outicustno']; 
?> 
<!------ �ǵ� outinvout_mod3.php   ------>
<form name="form1" method="post" action="outinvout_mod3.php">
  <table width="770" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
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
              <input type="submit" name="submit" value="�ק�P�f���">
            </td>
	  </tr>
  </table>
        <table width="770" border="0" cellpadding="1" cellspacing="1" bgcolor="#99CCFF" bordercolor="#0000FF">
          <tr>           
            <td width="241" align="center"><font >�P�f�渹</font></td>
            <td width="522" align="left"><?=$row['outino']?> 
		      <input  type="hidden" name="outino" size="10" value="<?=$row['outino']?>">
			  <input  type="hidden" name="oqty" size="10" value="<?=$oqty;?>">
			  <input  type="hidden" name="opric" size="10" value="<?=$opric;?>">
			  <input  type="hidden" name="ocust" size="10" value="<?=$ocust;?>">			 
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
			    <input type="hidden" name="outiprodname" size="40" value="<?=$row['prodname']?>">			   
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
            <td width="241" height="22" align="center"><font >�P�f���</font> </td>
            <td width="522" height="22" align="left">
                <input type="text" name="outidate" size="10" value="<?=$row['outidate']?>">
            </td>            
          </tr>          
		  <tr>
			<td width="241" height="22" align="center">���~�ƶq</td>
            <td width="522" height="22">
			<!------------------ �ק���ˬd���~�ƶq--------------> 
                <input type="text" name="outiprodqty" size="6" value="<?=$row['outiprodqty']?>" onblur="checkprodqty(this)">
            </td>           
          </tr>
		  <tr>
			<td width="241" height="22" align="center">���~���</td>
            <td width="522" height="22">
			<input type="text" name="outiunit" size="10" value="<?=$row['outiunit']?>">
             </td>           
          </tr>
		  <tr> 
            <td width="241" align="center">���~���</td>
            <td width="522"> 
			<!---------------- �ק���ˬd���~���-------------->
                <input type="text" name="outipric" size="10" value="<?=$row['outipric']?>"  onBlur="checkpric(this)">
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