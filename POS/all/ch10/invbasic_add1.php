<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?	
	include("mysqlcntdb.php");
	$cntid="prod";
	include("counter.php");
	// -------------���X�Ҧ����~���O�����---------------
	$SQLStr = "SELECT * FROM prty";
	$res = mysql_query($SQLStr);	
?>
<!------����ˬd,�ˬd��J����ƥ��T��----------------------->
<script language="JavaScript">
function validate(){
   var jfm = document.form1;
   var prodno = jfm.prodno[].value;  
   if (prodno == "" ){
      alert("�S����J���~�s��!");
      event.returnValue = false;
   }   
}
// --------------�ˬd���~�s��--------------
function checkprodno(fld){
   if (fld.value.length < 1){
      alert("�п�J���~�s��(�j��1�Ӧr��)!");
      fld.focus();
      fld.select();
   }
}

//-------------- �ˬd�ƶq--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("�п�J���~�ƶq!");
      fld.focus();
      fld.select();
   }
}

//-------------- �ˬd���--------------
function checkpric(fld){
   if (fld.value == ""){
      alert("�п�J���!");
      fld.focus();
      fld.select();
   }
}
</script>	
<!--���沣�~�򥻸�ƿ�J��,�i�Jinvdbasic_add2.php�s����Ʈw------->
<form name="form1" method="post" action="inv/invbasic_add2.php" onSubmit="validate();">
 <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#0000FF">
    <tr>
	  <td   bgcolor="#FFFFFF">  
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�s�W���~�򥻸��</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="�s�W���~���">
            </td>                 
          </tr>
        </table>
<!--���~�򥻸�ƿ�J------->		
        <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"   bordercolor="#FFFFFF" align="center">
          <tr> 
            <td width="103" align="center">���~�s��</td>
            <td width="187"> 
                <input type="text" name="prodno" size="10" value="<?=$prodcnt;?>"  onChange="checkprodno(this)">
            </td>
            <td width="96" align="center">���~�W��</td>
            <td width="351"> 
                <input type="text" name="prodname" size="40">
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">�W�满��</td>
            <td width="187"> 
                 <input type="text" name="prodsdesp" size="40">
            </td>
            <td width="96" align="center">���~���O</td>
            <td width="351">
<?php

	if ($res)
	{
	  $num = mysql_num_rows($res);
//------------------- �e�{���O�W�٪�����,�ѿ��------------------------------------
          echo "<select name='prodtype'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['prtyno'] . "'>" . $row['prtyname'] . "</option>";
	  }
            echo "</select>";
	
	}		
	else 
		echo "�ثe���~�L���O�Ϥ�";
?>              
            </td>
          </tr>
          <tr> 
            <td width="103" align="center">�����t��</td>
            <td width="187">
<?php
//-------------------- �N�t�Ӹ�ƪ�����ƥ������X----------------------------
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res);
//------------------- �e�{�t�ӦW�٪�����,�ѿ��------------------------------------
           echo "<select name='prodvend'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['vendno'] . "'>" . $row['vendname'] . "</option>";
	  }
            echo "</select>";	
	}		
	else 
		echo "�ثe�t�ӵL�W��";
?>
            </td>
            <td width="96" align="center">���</td>
            <td width="351">
<?php
//-------------------- �N���~����ƪ�����ƥ������X----------------------------
	$SQLStr = "SELECT * FROM prun";
	$res = mysql_query($SQLStr);	
	if ($res)
	{
	  $num = mysql_num_rows($res);
//------------------- �e�{���~���W�٪�����,�ѿ��------------------------------------
      echo "<select name='produnit'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['prunno'] . "'>" . $row['prunname'] . "</option>";
	  }
            echo "</select>";
	}		
	else 
		echo "�ثe���~���L�Ϥ�";
?>	       
            </td>
          </tr>
		   <tr> 
            <td width="103" align="center">��������</td>
            <td width="187"> 
                <input type="text" name="prodipric" size="10"  onChange="checkpric(this)">
            </td>
            <td width="96" align="center">���</td>
            <td width="351"> 
                <input type="text" name="prodspric" size="10">
            </td>
          </tr>
          <tr> 
            <td width="103" height="22" align="center">�w���s�q</td>
            <td width="187" height="22"> 
              <input type="text" name="prodsave" size="10">
            </td>
            <td width="96" height="22" align="center">�̪�i�f��</td>              
            <td width="187" height="22">
              <input type="text" name="prodidate" value="<?=date("Y-m-d")?>">
            </td>
          </tr>         
         <tr>
			<td width="103" height="22" align="center">�̪�X�f��</td>
            <td width="187" height="22"> 
			<input type="text" name="prododate" value="<?=date("Y-m-d")?>">                
            </td>           
          </tr>		     
        </table>
        <br>        
      </td>
    </tr>
  </table>
</form>
</body>
</html>
