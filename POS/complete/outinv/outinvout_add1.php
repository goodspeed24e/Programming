<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
	include("mysqlcntdb.php");
	$cntid="outi";	
	include("counter.php");
	$dt=date("Y-m-d");
//-------------- �N�Ȥ��ƪ�����ƥ������X--------------
	$SQLStr = "SELECT * FROM cust";
	$res = mysql_query($SQLStr);
?>
<script language="JavaScript">
//-------------- �ˬd�ƶq--------------
function checkprodqty(fld){
   if (fld.value == ""){
      alert("�п�J���~�ƶq!");
      fld.focus();
      fld.select();
   }
}
</script>
<form name="form1" method="post" action="outinv/outinvout_add2.php" >
  <table width="780" border="1" cellpadding="0" cellspacing="0" align="center" bordercolor="#000000" >
    <tr > <td   bgcolor="#FFFFFF">    
        <table  border="1" align="center" bgcolor="#99CCFF" cellpadding="0" cellspacing="0" width="780">
          <tr  bgcolor="#99CCFF"> 
            <td  bgcolor="#9933FF" align="center"> 
             <font color="#FFFFFF">�s�W�P�f����</font>
            </td> 
			  <td align="center"> 
              <input type="submit" name="submit" value="�s�W�P�f���">
            </td>                 
          </tr>
        </table>	
        <table width="780" border="1" cellpadding="0" cellspacing="0" bgcolor="#99CCFF"  align="center">
          <tr> 
            <td width="103" align="center">�P�f�渹</td>
            <td width="187"><input type="text" name="outino" size="10" value="<?=$outicnt;?>">                
            </td>
            <td width="96" align="center">�P�f���</td>
            <td width="351"> 
                <input type="text" name="outidate" size="12" value="<?=date("Y-m-d")?>">
            </td>
          </tr>        
          <tr>            
            <td width="96" height="22" align="center">�Ȥ�s��</td>
           <!-- </td>-->
            <td width="187" height="22">
<?
	if ($res)
	{
	  $num = mysql_num_rows($res);

//---------- �N�Ȥ�W�٪����ȧe�{������W-------------- 
          echo "<select name='outicustno'>";
	  for ($i=0;$i<$num;$i++)
	  {
	    $row = mysql_fetch_array($res);
	    echo "<option value='" . $row['custno'] . "'>" .$row['custno'] . "/" . $row['custname'] . "</option>";
	  }
            echo "</select>";
//-------------- �N�Ȥ�W�٪����ȥH�e�{������W--------------

	}		
	else //-------------- �Ȥ��ƪ��L�Ȥ���--------------
		echo "�ثe�L�Ȥ�Ϥ�";
?>           
            </td>
			 <td width="96" align="center">�����渹</td>
            <td width="351"> 
                <input type="text" name="outiquno" size="10" value="<?=$outiquno;?>">
            </td>
          </tr>        
        </table>       
        <table width="780"  border="1"   bgcolor="#99CCFF" cellpadding="0" cellspacing="0" align="center">
         <tr>
            <td  align="center" width="542">���~�s��/���~�W��/���/���</td>          
            <td width="238" align="center">�P�f�ƶq</td>  
          </tr>        
 <?php		  
//-------------- ��J�P�ⲣ�~�������--------------
	  for ($i=0;$i<8;$i++)
		 { 
          echo "<tr>";          
            echo "<td align='center'>";
//-------------- �N���~��ƪ�����ƥ������X--------------	
	$SQLStr = "SELECT product.*, prun.* FROM product AS product ";
	$SQLStr .= "LEFT JOIN prun AS prun ON product.produnit =  prun.prunno ";
	$res = mysql_query($SQLStr);
	if ($res)
	{
	  $num = mysql_num_rows($res); 
          echo "<select name='outiprodno[]'>";
	  for ($j=0;$j<$num;$j++)
	  {
	    $row = mysql_fetch_array($res);	
//-------------- �N���~���������ȧe�{������W--------------			
	    echo "<option value='" . $row['prodno'] . "'>" . $row['prodno'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;" . $row['prodname'] ."&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['prunname']. "&nbsp;&nbsp;&nbsp;/&nbsp;&nbsp;&nbsp;".$row['prodspric']. "</option>";
	  }
            echo "</select>";
//-------------- ��J�P��ƶq���ȥH�Χe�{������W--------------
     echo "</td>";			      
     echo "<td align='center'><input name='outiprodqty[]' type='text' size='6' maxlength='6' onblur='checkprodqty(this)'></td>";

	}		
	else
		echo "�ثe�L���~";			
    }
		  ?>	  
        </table>     
      </td>
    </tr>
  </table>
</form>
</body>
</html>
