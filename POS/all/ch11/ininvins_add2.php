<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php	
	include("mysqlcntdb.php");
	$cntid="tran";	
	include("counter.php");
	$dt=date("Y-m-d");
//-------------- �N�t�Ӹ�ƪ�����ƥ������X--------------
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);

?>
<!---------------- �������ˬd-------------->
<script language="JavaScript">
//-------------- �ˬd�ƶq--------------
function checkprodqty(objEle){
   if (objEle.value == ""){
      alert("�п�J���~�ƶq!");
      objEle.focus();
      objEle.select();
   }
}

</script>	
<!------�i�Jininvins_add3 ,�N�i�f��ƿ�J��Ʈw��---------->
<form name="form1" method="post" action="ininv/ininvins_add3.php">
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" >
    <tr> 
	<table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�s�W�i�f����</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="�s�W�i�f���">
            </td>                 
          </tr>
        </table>	
      <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">        
	      <tr> 
            <td width="103" align="center">�i�f�渹</td>
            <td width="187"><input type="text" name="tranno" size="10" value="<?=$trancnt;?>">                
            </td>
            <td width="96" align="center">�i�f���</td>
            <td width="351"> 
                <input type="text" name="trandate" size="12" value="<?=date("Y-m-d")?>">
            </td>
          </tr>
        
          <tr>            
            <td width="96" height="22" align="center">�t�ӽs��</td>
           <!-- </td>-->
            <td width="187" height="22"><?=$vendno;?><?=$vendname;?>
              <input  type="hidden" name="tranvendno" size="10" value="<?=$vendno;?>">
            </td>
			<td width="96" align="center">���ʳ渹</td>
            <td width="351"> 
                <input type="text" name="tranpono" size="12" value="<?=$tranpono;?>">
            </td>
          </tr>        
        </table>       
		<table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">        
          <tr>
            <td  align="center" width="542">���~�s��/���~�W��/���/���</td>          
            <td width="238" align="center">�i�f�ƶq</td>  
          </tr>
  <?php		  
//-------------- �H�U�Ԧ��e�{�P�@�t�Ӳ��~,�ѿ�ܶi�f���~�������--------------
	  for ($i=0;$i<8;$i++)
		 { 
          echo "<tr>";          
            echo "<td align='center'>";
//-------------- �N���~��ƪ��ŦX���󪺸�ƥ������X,�P�ɥHJOIN�覡�����~������ܦW��--------------	
	$SQLStr = "SELECT product.*, prun.* FROM product AS product ";
	$SQLStr .= "LEFT JOIN prun AS prun ON product.produnit =  prun.prunno WHERE prodvend='$vendno'";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res); 
          echo "<select name='tranprodno[]'>";
	  for ($j=0;$j<$num;$j++)
	  {
	    $row = mysql_fetch_array($res);		
	    echo "<option value='" . $row['prodno'] . "'>" . $row['prodno'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;" . $row['prodname'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['prunname']. "&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['prodipric']. "</option>";
	  }
            echo "</select>";
    echo "</td>";			      
     echo "<td align='center'><input name='tranprodqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";

	}		
	else
		echo "�ثe�����Ѳ��~���";			
    }
 ?>	  
        </table>     
      </td>
    </tr>
  </table>
</form>
</body>
</html>
